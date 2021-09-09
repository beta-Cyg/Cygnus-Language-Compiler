#ifndef CYG_GRAMMAR_TREE_H
#define CYG_GRAMMAR_TREE_H

#include<string>
#include<fstream>
#include<exception>
#include<initializer_list>

namespace cyg{
	namespace grammar_tree{
		typedef long double real;

		class base_struct{
		public:
			base_struct* next;
			virtual base_struct(base_struct* _next=nullptr):next(_next)noexcept{}
		};//base class of the tree node

		class import_struct:public base_struct{
		public:
			std::string module_name;
			base_struct* next;
			import_struct(std::string mn="",base_struct* _next=nullptr):module_name(mn),next(_next)noexcept{}
		};

		class value_struct:public base_struct{
		public:
			std::string value_name;
			base_struct* child;
			base_struct* next;
			value_struct(std::string vn="",base_struct* _child=nullptr,base_struct* _next=nullptr):value_name(vn),child(_child),next(_next){}
		};

		class expression{
			std::string exp;

			const real& operate(initializer_list<real> args){
				real result;
				return result;
			}
		};//todo finish the function operate of the class expression

		class g_tree_error_code:public std::exception{
		public:
			std::string code_type;

			g_tree_error_code()noexcept{}

			g_tree_error_code(std::string&& c_t):code_type(c_t)noexcept{}

			const char* what(){
				return code_type.c_str();
			}
		};
		
		class g_tree{
		private:
			base_struct* root;
			std::string code;
		public:
			g_tree(const std::string& _code):root(nullptr),code(_code){
			}
			
			~g_tree(){
				clear();
			}

			void clear(){
			}
		};

		g_tree parse(std::string file_name){
			ifstream fin(file_name);
			std::string file_str="",buf;
			while(getline(fin,buf))file_str+=buf;
			fin.close();
		}
	}
}

#endif
