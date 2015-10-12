#ifndef DYNAMIC_LIB_HANDLER_CLASS_HPP
# define DYNAMIC_LIB_HANDLER_CLASS_HPP

# include <IGraphic.class.hpp>
# include <stdexcept>

class DynamicLibHandler {

	public:
		~DynamicLibHandler(void);

		static DynamicLibHandler & instance(void);

		IGraphic *		getLib(void) const;
		void *			getHandle(void) const;
		void			setHandle(std::string & path, int width, int height);

		class DLibOpenException : public std::exception {
			virtual const char * what (void) const throw () {
				return "Error opening library.";
			}
		};

		class DLibInitException : public std::exception {
			virtual const char * what (void) const throw () {
				return "Error initializing library.";
			}
		};

		class DLibDestroyException : public std::exception {
			virtual const char * what (void) const throw () {
				return "Error destroying library.";
			}
		};

	private:
		DynamicLibHandler(void);
		DynamicLibHandler(DynamicLibHandler const & ref);
		DynamicLibHandler & operator=(DynamicLibHandler const & ref);

		void			_closeHandle(void);
		void			_initLib(int width, int height);
		void			_destroyLib(void);

		void *			_handle;
		IGraphic *		_lib;

};

#endif
