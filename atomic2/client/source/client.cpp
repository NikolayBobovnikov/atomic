#include "employee.grpc.pb.h"
#include "employee_dto.h"
#include <chrono>
#include <functional>
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

  void insert_employee(const EmployeeDTO &e) const
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

  optional<EmployeeDTO> get_employee(size_t id) const
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

  std::vector<EmployeeDTO> get_employees() const
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

  optional<string> get_employee_position(size_t id) const
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

  optional<EmployeeDTO> get_employee_manager(size_t employee_id) const
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

  void set_employee_position(size_t id, const std::string &position) const
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

  void set_employee_manager(size_t emp_id, size_t manager_id) const
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

  void delete_employee(size_t id) const
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

void
benchmark(size_t requestCount, const std::string &method_name, std::function<void(void)> method)
{
  std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

  try
  {
    for (size_t i = 0; i < requestCount; ++i)
    {
      method();
    }
  }
  catch (exception &e)
  {
    cout << e.what() << endl;
  }

  std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

  auto seconds = std::chrono::duration_cast<std::chrono::seconds>(end - begin).count();
  std::cout << method_name << ": " << std::to_string((size_t) (requestCount / seconds)) << " rps" << std::endl;
}

void
print_employees(const EmployeesClient &client)
{
  auto employees = client.get_employees();

  cout << "Server contains the following employees: " << endl;
  for (const auto &e : employees)
  {
    cout << "Name:" << e.name << ", position: " << e.position << endl;
  }
}

int
main(int argc, char **argv)
{
  EmployeesClient client(grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials()));
  // print_employees();

  const size_t requestsCount = 1000;
  size_t id = 0;

  auto get_employee = [&client]() { client.get_employee(1); };
  auto get_employee_manager = [&]() { client.get_employee_manager(1); };
  auto get_employee_position = [&]() { client.get_employee_position(1); };
  auto get_employees = [&]() { client.get_employees(); };
  auto insert_employee = [&]() { client.insert_employee(TestEmployee()); };
  auto set_employee_manager = [&]() { client.set_employee_manager(1, 1); };
  auto set_employee_position = [&]() { client.set_employee_position(1, "New position"); };
  auto delete_employee = [&]() { client.delete_employee(++id); };

  benchmark(requestsCount, "get_employee", get_employee);
  benchmark(requestsCount, "get_employee_manager", get_employee_manager);
  benchmark(requestsCount, "get_employee_position", get_employee_position);
  benchmark(requestsCount, "get_employees", get_employees);
  benchmark(requestsCount, "insert_employee", insert_employee);
  benchmark(requestsCount, "set_employee_manager", set_employee_manager);
  benchmark(requestsCount, "set_employee_position", set_employee_position);
  benchmark(requestsCount, "set_employee_position", set_employee_position);

  return 0;
}
