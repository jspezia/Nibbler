#ifndef DYNAMIC_LIB_HANDLER_CLASS_HPP
# define DYNAMIC_LIB_HANDLER_CLASS_HPP

# include <IGraphic.class.hpp>

class DynamicLibHandler {

public:
	DynamicLibHandler(void);
	~DynamicLibHandler(void);
	DynamicLibHandler(DynamicLibHandler const & ref);
	DynamicLibHandler & operator=(DynamicLibHandler const & ref);

	static DynamicLibHandler & instance(void);

	IGraphic *		getLib(void) const;
	void *			getHandle(void) const;
	void			setHandle(std::string & path, int width, int height);

private:
	void			_closeHandle(void);
	void			_initLib(int width, int height);
	void			_destroyLib(void);

	void *			_handle;
	IGraphic *		_lib;

};

#endif
