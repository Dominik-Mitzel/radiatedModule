#include "gainAnalysis.h"

#include <TColor.h>
#include <TStyle.h>
#include <TSystem.h>

//from BOOST
#include "boost/program_options.hpp"
#include "boost/filesystem.hpp"

namespace po = boost::program_options;
namespace fs = boost::filesystem;


//static const char *optString = "l:u:?";
struct config{
  std::string arg_pathToFile;      /* -l option */
  unsigned int arg_uplink;      /* -u option */
};

int parseOptions(config &c, int argc, char *argv[]){
  // declare options
  po::options_description desc("Allowed options") ;
  desc.add_options()
  ("help,h", "show this help")
  ("l", po::value<std::string>(&c.arg_pathToFile), "led run number")
  ("u", po::value<unsigned int>(&c.arg_uplink)->default_value(0), "uplink ID")
  ;

  // actually do the parsing
  po::variables_map vm;
  po::store(po::parse_command_line(argc, argv, desc), vm);
  po::notify(vm);

  // show help and exit
  if ((vm.count("help"))) {
     std::cout << desc << "\n";
     return 1;
  }

  return 0;
}


int main(int argc, char** argv){

  config cfg;
  if (parseOptions(cfg, argc, argv)!= 0){
    std::cerr << "Can not parse options!" << std::endl;
    return 0;
  }


  TApplication myapp("myapp",0,0);
  setRootStyle();

  //Give folder in which the data is stored
  std::string foldername;
  //foldername = "/data/testbeam_data/";
  // foldername = "/home/scifi_testbeam14/MirrorStudy/";
  //foldername = "/home/scifi_testbeam14/data/testbeam2015Nov/";
  foldername = "/home/scifi_testbeam14/radiatedModule/";
  //The name of the led file is btsoftware_<runnumber>_calib_led_ntuple.root
  std::stringstream filename_stream;
  filename_stream.str(std::string());
  filename_stream << foldername << "btsoftware_" << cfg.arg_pathToFile << "_calib_led_ntuple.root";

  //The output gain file will be saved in a new folder led_gain/ in the data folder
  std::stringstream gainname_stream;
  gainname_stream.str(std::string());
  gainname_stream << foldername << "led_gain/";

  fs::path p(gainname_stream.str().c_str());
  if (!fs::is_directory(p)) fs::create_directories(p);

  //The name of the led gain file is btsoftware_<runnumber>_calib_led_gain_uplink<uplinkNumber>.root
  gainname_stream << "btsoftware_" << cfg.arg_pathToFile << "_calib_led_gain_uplink" << cfg.arg_uplink << ".root";

  std::cout<<"LED-filename = " << filename_stream.str().c_str();
  std::cout<<"gainname = " << gainname_stream.str().c_str();

  //execute gainAnalysis
  gainAnalysis(filename_stream.str().c_str(), gainname_stream.str().c_str(), cfg.arg_uplink);

  gSystem->ProcessEvents();
   myapp.Run();
  getchar();
  return 0;

}
