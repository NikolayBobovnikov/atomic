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

using namespace std;
using namespace std::chrono;

class EmployeesImpl final : public Employees::Service
{
public:
  explicit EmployeesImpl(const string &db_path) : m_db(db_path) {}

  Status GetEmployee(ServerContext *context, const workers::EmployeeId *request, workers::EmployeeId *response)
  {
    m_db.get_employee(request->id());
    return Status::OK;
  }

  Status InsertEmployee(ServerContext *context, const workers::Employee *request, workers::EmployeeId *response)
  {
    response->set_id(m_db.insert_employee({request->name(), request->position()}));
    return Status::OK;
  }

  Status ListEmployees(ServerContext *context, const workers::EmptyMessage *request,
                       ServerWriter<workers::Employee> *writer)
  {
    for (const auto &e : m_db.get_employees())
    {
      workers::Employee we;
      we.set_id(e.id);
      we.set_name(e.name);
      we.set_position(e.position);

      if (e.manager_id.has_value())
      {
        we.set_manager_id(e.manager_id.value());
      }

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
    m_db.delete_employee(request->id());
    return Status::OK;
  }

private:
  vector<Employee> m_employee_list;
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

  EmployeesImpl service(db_path);
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
