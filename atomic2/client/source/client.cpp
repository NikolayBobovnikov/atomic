#include "employee.grpc.pb.h"
#include "employee_dto.h"
#include <chrono>
#include <grpc/grpc.h>
#include <grpcpp/channel.h>
#include <grpcpp/client_context.h>
#include <grpcpp/create_channel.h>
#include <grpcpp/security/credentials.h>
#include <iostream>
#include <memory>
#include <optional>
#include <random>
#include <string>
#include <thread>

using grpc::Channel;
using grpc::ClientContext;
using grpc::ClientReader;
using grpc::ClientReaderWriter;
using grpc::ClientWriter;
using grpc::Status;
using proto::Employees;

using namespace std;
using namespace DB;
class EmployeesClient
{
public:
  EmployeesClient(shared_ptr<Channel> channel) : stub_(Employees::NewStub(channel)) {}

  void insert_employee(const EmployeeDTO &e)
  {
    // Data we are sending to the server.
    proto::Employee request;
    request.set_name(e.name);
    request.set_position(e.position);

    // Container for the data we expect from the server.
    proto::EmployeeId reply;

    // Context for the client. It could be used to convey extra information to
    // the server and/or tweak certain RPC behaviors.
    ClientContext context;

    // The actual RPC.
    Status status = stub_->InsertEmployee(&context, request, &reply);
  }

  optional<EmployeeDTO> get_employee(size_t id)
  {
    optional<EmployeeDTO> result;

    // Data we are sending to the server.
    proto::EmployeeId request;
    request.set_id(id);

    // Container for the data we expect from the server.
    proto::Employee reply;

    // Context for the client. It could be used to convey extra information to
    // the server and/or tweak certain RPC behaviors.
    ClientContext context;

    // The actual RPC.
    Status status = stub_->GetEmployee(&context, request, &reply);

    // Act upon its status.
    if (status.ok())
    {
      result = EmployeeDTO();
    }

    return result;
  }

  // std::vector<EmployeeDTO> get_employees() {}
  // std::string get_employee_position(size_t emp_id) {}
  // std::optional<size_t> get_employee_manager_id(size_t emp_id) {}
  // void set_employee_position(size_t emp_id, const std::string &position) {}
  // void set_employee_manager(size_t emp_id, size_t manager_id) {}
  // void delete_employee(size_t emp_id) {}

private:
  unique_ptr<Employees::Stub> stub_;
};

int
main(int argc, char **argv)
{
  EmployeesClient client(grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials()));
  client.insert_employee(TestEmployee());
  return 0;
}
