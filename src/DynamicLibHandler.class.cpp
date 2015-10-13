#include <dlfcn.h>
#include <iostream>
#include <DynamicLibHandler.class.hpp>
#include <Lib.hpp>

DynamicLibHandler::DynamicLibHandler(void) : _handle(NULL), _lib(NULL) {}

DynamicLibHandler::~DynamicLibHandler(void)
{
	this->_closeHandle();
}

DynamicLibHandler::DynamicLibHandler(DynamicLibHandler const & ref)
{
	*this = ref;
}

DynamicLibHandler & DynamicLibHandler::operator=(DynamicLibHandler const & ref)
{
	this->_handle = ref.getHandle();
	this->_lib = ref.getLib();
	return *this;
}

DynamicLibHandler &		DynamicLibHandler::instance(void)
{
	static DynamicLibHandler	DLhandler;

	return DLhandler;
}

/* GETTERS */

void *					DynamicLibHandler::getHandle(void) const
{
	return this->_handle;
}

IGraphic *				DynamicLibHandler::getLib(void) const
{
	return this->_lib;
}

/* SETTERS */

void					DynamicLibHandler::setHandle(std::string & path, int width, int heigth)
{
	this->_closeHandle();

	this->_handle = dlopen(path.c_str(), RTLD_LAZY);
	if (!this->_handle) {
		std::cerr << "Error: " << dlerror() << std::endl;
		throw DLibOpenException();
	}

	try {
		this->_initLib(width, heigth);
	} catch (std::exception & e) {
		std::cerr << e.what() << std::endl;
		exit(0);
	}
}

void					DynamicLibHandler::_closeHandle(void)
{
	if (this->_handle)
	{
		try {
			this->_destroyLib();
		} catch (std::exception & e) {
			std::cerr << e.what() << std::endl;
			exit(0);
		}
		dlclose(this->_handle);
	}
}

void					DynamicLibHandler::_initLib(int width, int heigth)
{
	IGraphic *		(*DL_init)(int, int);

	DL_init = (IGraphic *(*)(int, int)) dlsym(this->_handle, "init");
	if (!DL_init) {
		throw DLibInitException();
	}
	this->_lib = DL_init(width, heigth);
}

void					DynamicLibHandler::_destroyLib(void)
{
	IGraphic *		(*DL_destroy)(IGraphic *);

	if (this->_lib)
	{
		DL_destroy = (IGraphic *(*)(IGraphic *)) dlsym(this->_handle, "destroy");
		if (!DL_destroy) {
			throw DLibDestroyException();
		}
		DL_destroy(this->_lib);
		this->_lib = NULL;
	}
}
