#ifndef FILE_STRING_API_H
#define FILE_STRING_API_H

#include<fstream>
#include<vector>
#include<string>
#include<exception>

namespace cyg{
	namespace modules{
		class token_exception:std::exception{
		public:
			int exception_type;
			std::string exception_name;
			token_expection(int e_type=0,std::string e_name=""):exception_type(e_type),exception_name(e_name){}
		};

		std::vector<std::string> get_token_from_module(std::string module_name){
			std::vector<std::string>token_name;
			std::fstream fin(std::ios::in);
		}//todo finish this func
	}

	namespace string_api{
		remove_space(string& value){}
	}
}

#endif
