#include <algorithm>
#include <chrono>
#include <cmath>
#include <iostream>
#include <memory>
#include <string>

#include "employee.grpc.pb.h"
#include <grpc/grpc.h>
#include <grpcpp/security/server_credentials.h>
#include <grpcpp/server.h>
#include <grpcpp/server_builder.h>
#include <grpcpp/server_context.h>

#include "database.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::ServerReader;
using grpc::ServerReaderWriter;
using grpc::ServerWriter;
using grpc::Status;
using std::chrono::system_clock;
using workers::Employee;
using workers::Employees;
using workers::Feature;
using workers::Point;
using workers::Rectangle;
using workers::RouteNote;
using workers::RouteSummary;

using namespace std;
using namespace std::chrono;

float
ConvertToRadians(float num)
{
  return num * 3.1415926 / 180;
}

// The formula is based on http://mathforum.org/library/drmath/view/51879.html
float
GetDistance(const Point &start, const Point &end)
{
  const float kCoordFactor = 10000000.0;
  float lat_1 = start.latitude() / kCoordFactor;
  float lat_2 = end.latitude() / kCoordFactor;
  float lon_1 = start.longitude() / kCoordFactor;
  float lon_2 = end.longitude() / kCoordFactor;
  float lat_rad_1 = ConvertToRadians(lat_1);
  float lat_rad_2 = ConvertToRadians(lat_2);
  float delta_lat_rad = ConvertToRadians(lat_2 - lat_1);
  float delta_lon_rad = ConvertToRadians(lon_2 - lon_1);

  float a = pow(sin(delta_lat_rad / 2), 2) + cos(lat_rad_1) * cos(lat_rad_2) * pow(sin(delta_lon_rad / 2), 2);
  float c = 2 * atan2(sqrt(a), sqrt(1 - a));
  int R = 6371000;   // metres

  return R * c;
}

string
GetFeatureName(const Point &point, const vector<Feature> &feature_list)
{
  for (const Feature &f : feature_list)
  {
    if (f.location().latitude() == point.latitude() && f.location().longitude() == point.longitude())
    {
      return f.name();
    }
  }
  return "";
}

class RouteGuideImpl final : public Employees::Service
{
public:
  explicit RouteGuideImpl(const string &db_path) : m_db(db_path) {}

  Status GetEmployee(ServerContext *context, const workers::EmployeeId *request, workers::EmployeeId *response)
  {
    m_db.get_employee(request->id());
    return Status::OK;
  }

  Status InsertEmployee(ServerContext *context, const workers::EmployeeData *request, workers::EmployeeId *response)
  {
    response->set_id(m_db.insert_employee({request->name(), request->position()}));
    return Status::OK;
  }

  Status ListEmployees(ServerContext *context, const workers::ListEmployeesRequest *request,
                       ServerWriter<workers::Employee> *writer)
  {
    for (const auto &e : m_db.get_employees())
    {
      workers::Employee we;
      we.set_id(e.id);
      if (e.manager_id.has_value())
      {
        we.set_manager_id(e.manager_id.value());
      }
      we.set_name(e.name);
      we.set_position(e.position);
      writer->Write(we);
    }
    return Status::OK;
  }

  Status GetEmployeePosition(ServerContext *context, const workers::EmployeeId *request,
                             workers::EmployeePosition *response)
  {
    response->set_position(m_db.get_employee_position(request->id()));
    return Status::OK;
  }

  Status GetEmployeeManager(ServerContext *context, const workers::EmployeeId *request, workers::Employee *response)
  {
    auto manager_id = m_db.get_employee_manager_id(request->id());
    if (manager_id.has_value())
    {
      response->set_manager_id(manager_id.value());
    }

    return Status::OK;
  }

  Status SetEmployeePosition(ServerContext *context, const workers::SetEmployeePositionRequest *request,
                             workers::SetEmployeePositionResponce *response)
  {
    m_db.set_employee_position(request->id(), request->position());

    return Status::OK;
  }

  Status SetEmployeeManager(ServerContext *context, const workers::SetEmployeeManagerRequest *request,
                            workers::SetEmployeeManagerResponce *response)
  {
    m_db.set_employee_manager(request->id(), request->manager_id());

    return Status::OK;
  }

  Status DeleteEmployee(ServerContext *context, const workers::EmployeeId *request,
                        workers::DeleteEmployeeResponce *response)
  {
    return Status::OK;
  }

  Status GetFeature(ServerContext *context, const Point *point, Feature *feature) override
  {
    feature->set_name(GetFeatureName(*point, feature_list_));
    feature->mutable_location()->CopyFrom(*point);
    return Status::OK;
  }

  Status ListFeatures(ServerContext *context, const workers::Rectangle *rectangle,
                      ServerWriter<Feature> *writer) override
  {
    auto lo = rectangle->lo();
    auto hi = rectangle->hi();
    long left = (min) (lo.longitude(), hi.longitude());
    long right = (max) (lo.longitude(), hi.longitude());
    long top = (max) (lo.latitude(), hi.latitude());
    long bottom = (min) (lo.latitude(), hi.latitude());
    for (const Feature &f : feature_list_)
    {
      if (f.location().longitude() >= left && f.location().longitude() <= right && f.location().latitude() >= bottom &&
          f.location().latitude() <= top)
      {
        writer->Write(f);
      }
    }
    return Status::OK;
  }

  Status RecordRoute(ServerContext *context, ServerReader<Point> *reader, RouteSummary *summary) override
  {
    Point point;
    int point_count = 0;
    int feature_count = 0;
    float distance = 0.0;
    Point previous;

    system_clock::time_point start_time = system_clock::now();
    while (reader->Read(&point))
    {
      point_count++;
      if (!GetFeatureName(point, feature_list_).empty())
      {
        feature_count++;
      }
      if (point_count != 1)
      {
        distance += GetDistance(previous, point);
      }
      previous = point;
    }
    system_clock::time_point end_time = system_clock::now();
    summary->set_point_count(point_count);
    summary->set_feature_count(feature_count);
    summary->set_distance(static_cast<long>(distance));
    auto secs = chrono::duration_cast<chrono::seconds>(end_time - start_time);
    summary->set_elapsed_time(secs.count());

    return Status::OK;
  }

  Status RouteChat(ServerContext *context, ServerReaderWriter<RouteNote, RouteNote> *stream) override
  {
    RouteNote note;
    while (stream->Read(&note))
    {
      unique_lock<mutex> lock(mu_);
      for (const RouteNote &n : received_notes_)
      {
        if (n.location().latitude() == note.location().latitude() &&
            n.location().longitude() == note.location().longitude())
        {
          stream->Write(n);
        }
      }
      received_notes_.push_back(note);
    }

    return Status::OK;
  }

private:
  vector<Employee> m_employee_list;
  vector<Feature> feature_list_;
  mutex mu_;
  vector<RouteNote> received_notes_;
  DB::SQLiteDb m_db;
};

void
RunServer(const string &db_path)
{
  using namespace DB;

  string server_address("0.0.0.0:50051");
  DB::Employee e = DB::TestEmployee();

  auto storage = DB::initDatabase(db_path);
  storage.insert(e);

  RouteGuideImpl service(db_path);
  ServerBuilder builder;
  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
  builder.RegisterService(&service);
  unique_ptr<Server> server(builder.BuildAndStart());
  cout << "Server listening on " << server_address << endl;
  server->Wait();
}

int
main(int argc, char **argv)
{
  string db = "employees.db";
  RunServer(db);

  return 0;
}
