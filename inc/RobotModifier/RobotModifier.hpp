#pragma once
#include <openrave/openrave.h>
#include <openrave/plugin.h>

class HttpServer;

namespace RobotModifier {


class RobotModifier : public OpenRAVE::ModuleBase
{
public:
    RobotModifier(OpenRAVE::EnvironmentBasePtr envPtr);
    virtual ~RobotModifier();
    void Destroy() override;
    void Reset() override;
    int main(const std::string& cmd);
    bool loadFile(std::ostream& sout, std::istream& sin);
    bool getBodies(std::ostream& sout, std::istream& sin);
    
private:
    OpenRAVE::EnvironmentBasePtr m_envPtr;
    std::unique_ptr<HttpServer> m_serverPtr;
    
};


} //namespace RobotModifier
