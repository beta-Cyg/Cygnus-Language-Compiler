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
			base_struct(base_struct* _next=nullptr):next(_next){}
		};//base class of the tree node

		class import_struct:public base_struct{
		public:
			std::string module_name;
			base_struct* next;
			import_struct(std::string mn="",base_struct* _next=nullptr):module_name(mn),next(_next){}
		};

		class value_struct:public base_struct{
		public:
			std::string value_name;
			base_struct* child;
			base_struct* next;
			value_struct(std::string vn="",base_struct* _child=nullptr,base_struct* _next=nullptr):value_name(vn),child(_child),next(_next){}
		};

		class expression{
		public:
			std::string exp;

			expression(){}

			expression(std::string&& _exp){
				*this=_exp;
			}

			expression(const char* _exp){
				*this=_exp;
			}

			const expression& operator=(std::string&& _exp){
				exp=_exp;
				return *this;
			}

			const expression& operator=(const std::string& _exp){
				exp=_exp;
				return *this;
			}

			const expression& operator=(const char* _exp){
				exp=_exp;
				return *this;
			}

			std::string parse(){
				return exp;//todo
			}
		};//todo finish the function operate of the class expression

		class if_struct:public base_struct{
		public:
			expression bool_exp;
			base_struct* child;
			base_struct* next;
			if_struct(expression bexp="false",base_struct* _child=nullptr,base_struct* _next=nullptr):bool_exp(bexp),child(_child),next(_next){}
		};

		class for_struct:public base_struct{
		public:
			value_struct for_value;
			expression bool_exp;
			expression change_exp;
			base_struct* child;
			base_struct* next;
			for_struct(value_struct fv=value_struct(),expression bexp="false",expression cexp="",base_struct* _child=nullptr,base_struct* _next=nullptr):for_value(fv),bool_exp(bexp),change_exp(cexp),child(_child),next(_next){}
		};

		class while_struct:public base_struct{
		public:
			expression bool_exp;
			base_struct* child;
			base_struct* next;
			while_struct(expression bexp="false",base_struct* _child=nullptr,base_struct* _next=nullptr):bool_exp(bexp),child(_child),next(_next){}
		};

		class g_tree_error_code:public std::exception{
		public:
			std::string code_type;

			g_tree_error_code()noexcept{}

			g_tree_error_code(std::string&& c_t):code_type(c_t){}

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
			std::ifstream fin(file_name);
			std::string file_str="",buf;
			while(getline(fin,buf))file_str+=buf;
			fin.close();
			g_tree gt(file_str);
			return gt;
		}
	}
}

#endif

