#include "RobotModifier/RobotModifier.hpp"
#include "HttpServer/HttpServer.hpp"
#include "sys/sys.hpp"

namespace RobotModifier {

RobotModifier::RobotModifier(OpenRAVE::EnvironmentBasePtr envPtr) : ModuleBase(envPtr), m_envPtr(envPtr){
    
    __description="This plugin is used to retrieve, modify robot in collada";
    RegisterCommand("loadFile", 
        [this](std::ostream& sout, std::istream& sin)
        {
            return loadFile(sout, sin);
        }, "load a given file");
    RegisterCommand("loadFile", 
        [this](std::ostream& sout, std::istream& sin)
        {
            return getBodies(sout, sin);
        }, "return bodies");
}


void RobotModifier::Destroy(){
    RAVELOG_INFO("module unloaded from environment\n");
}


void RobotModifier::Reset(){
    RAVELOG_INFO("module reset\n");
}

bool RobotModifier::loadFile(std::ostream& sout, std::istream& sin){
    std::string filename;
    sin >> filename;
    bool bSuccess = GetEnv()->Load(filename.c_str());   // load the file
    return bSuccess;
}

bool RobotModifier::getBodies(std::ostream& sout, std::istream& sin){
    std::vector<OpenRAVE::KinBodyPtr> vbodies;
    GetEnv()->GetBodies(vbodies);
    sout << vbodies.size();     // publish the results
    return true;
}

int RobotModifier::main(const std::string& cmd){
    RAVELOG_INFO("module initialized cmd; %s\n", cmd.c_str());
    sys::setup();
    m_serverPtr = std::make_unique<HttpServer>(sys::getIoContext(), 9000);
    m_serverPtr->start();
    sys::run();
    return 0;
}

}



OpenRAVE::InterfaceBasePtr CreateInterfaceValidated(OpenRAVE::InterfaceType type, const std::string& interfacename, std::istream& sinput, OpenRAVE::EnvironmentBasePtr penv)
{
    if( type == OpenRAVE::PT_Module && interfacename == "mymodule" ) {
        return OpenRAVE::InterfaceBasePtr(new RobotModifier::RobotModifier(penv));
    }
    return OpenRAVE::InterfaceBasePtr();
}

void GetPluginAttributesValidated(OpenRAVE::PLUGININFO& info)
{
    info.interfacenames[OpenRAVE::PT_Module].push_back("MyModule");
}

OPENRAVE_PLUGIN_API void DestroyPlugin()
{
    RAVELOG_INFO("destroying plugin\n");
}
