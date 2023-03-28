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

namespace
{
EmployeeDTO
from_proto(const proto::Employee &e)
{
  return {e.id(), e.manager_id(), e.name(), e.position()};
}
}   // namespace
class EmployeesClient
{
public:
  EmployeesClient(shared_ptr<Channel> channel) : m_stub(Employees::NewStub(channel)) {}

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
    Status status = m_stub->InsertEmployee(&context, request, &reply);
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
    Status status = m_stub->GetEmployee(&context, request, &reply);

    // Act upon its status.
    if (status.ok())
    {
      result = EmployeeDTO();
    }

    return result;
  }

  std::vector<EmployeeDTO> get_employees()
  {
    proto::EmptyMessage request;
    proto::Employee reply;
    vector<EmployeeDTO> employees;
    ClientContext context;

    std::unique_ptr<ClientReader<proto::Employee>> reader(m_stub->ListEmployees(&context, request));
    while (reader->Read(&reply))
    {
      employees.emplace_back(reply.id(), reply.manager_id(), reply.name(), reply.position());
    }

    Status status = reader->Finish();
    return employees;
  }

  optional<string> get_employee_position(size_t id)
  {
    optional<string> result;

    // Data we are sending to the server.
    proto::EmployeeId request;
    request.set_id(id);

    // Container for the data we expect from the server.
    proto::EmployeePosition reply;

    // Context for the client. It could be used to convey extra information to
    // the server and/or tweak certain RPC behaviors.
    ClientContext context;

    // The actual RPC.
    Status status = m_stub->GetEmployeePosition(&context, request, &reply);

    // Act upon its status.
    result = status.ok() ? reply.position() : result;

    return result;
  }

  optional<EmployeeDTO> get_employee_manager(size_t employee_id)
  {
    optional<EmployeeDTO> result;

    // Data we are sending to the server.
    proto::EmployeeId request;
    request.set_id(employee_id);

    // Container for the data we expect from the server.
    proto::Manager reply;

    // Context for the client. It could be used to convey extra information to
    // the server and/or tweak certain RPC behaviors.
    ClientContext context;

    // The actual RPC.
    Status status = m_stub->GetEmployeeManager(&context, request, &reply);

    // Act upon its status.
    optional<proto::Employee> manager;
    manager = status.ok() ? reply.employee() : manager;
    result = manager.has_value() ? from_proto(manager.value()) : result;
    return result;
  }

  void set_employee_position(size_t id, const std::string &position)
  {
    // Data we are sending to the server.
    proto::SetEmployeePositionRequest request;
    request.set_id(id);
    request.set_position(position);

    // Container for the data we expect from the server.
    proto::SetEmployeePositionResponce reply;

    // Context for the client. It could be used to convey extra information to
    // the server and/or tweak certain RPC behaviors.
    ClientContext context;

    // The actual RPC.
    Status status = m_stub->SetEmployeePosition(&context, request, &reply);
  }

  void set_employee_manager(size_t emp_id, size_t manager_id)
  {
    // Data we are sending to the server.
    proto::SetEmployeeManagerRequest request;
    request.set_id(emp_id);
    request.set_manager_id(manager_id);

    // Container for the data we expect from the server.
    proto::SetEmployeeManagerResponce reply;

    // Context for the client. It could be used to convey extra information to
    // the server and/or tweak certain RPC behaviors.
    ClientContext context;

    // The actual RPC.
    Status status = m_stub->SetEmployeeManager(&context, request, &reply);
  }

  void delete_employee(size_t id)
  {   // Data we are sending to the server.
    proto::EmployeeId request;
    request.set_id(id);

    // Container for the data we expect from the server.
    proto::DeleteEmployeeResponce reply;

    // Context for the client. It could be used to convey extra information to
    // the server and/or tweak certain RPC behaviors.
    ClientContext context;

    // The actual RPC.
    Status status = m_stub->DeleteEmployee(&context, request, &reply);
  }

private:
  unique_ptr<Employees::Stub> m_stub;
};

int
main(int argc, char **argv)
{
  EmployeesClient client(grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials()));
  auto employees = client.get_employees();

  cout << "Server contains the following employees: " << endl;
  for (const auto &e : employees)
  {
    cout << "Name:" << e.name << ", position: " << e.position << endl;
  }
  return 0;
}
