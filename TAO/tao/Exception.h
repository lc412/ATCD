// This may look like C, but it's really -*- C++ -*-
//
// $Id$

// ============================================================================
//
// = LIBRARY
//    TAO
//
// = FILENAME
//    Exception.h
//
// = DESCRIPTION
//     This file defines way in which CORBA exceptions are reported.
//
// = AUTHOR
//     Copyright 1994-1995 by Sun Microsystems Inc.
//
// ============================================================================

#ifndef TAO_EXCEPTION_H
#define TAO_EXCEPTION_H
#include "ace/pre.h"

#include "tao/corbafwd.h"

#if !defined (ACE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */


// This is used in the implementation of the _raise methods
#if defined (TAO_HAS_EXCEPTIONS)
#define TAO_RAISE(EXCEPTION) throw EXCEPTION
#else
#define TAO_RAISE(EXCEPTION)
#endif /* TAO_HAS_EXCEPTIONS */


class CORBA_Any;
class TAO_OutputCDR;
class TAO_InputCDR;

class TAO_Export CORBA_Exception
{
  // = TITLE
  //   CORBA_Exception
  //
  // = DESCRIPTION
  //   CORBA2-specified exception hierarchy.  All exceptions have a
  //   type (represented by a TypeCode) and a widely scoped type ID
  //   (in the TypeCode) that generated by any OMG-IDL compiler and
  //   available through the Interface Repositories.  Think of it as a
  //   "globally scoped" name distinguishing each exception.
public:
  // = Initialization and termination methods.
  CORBA_Exception (const CORBA_Exception &src);
  // Copy constructor.

  CORBA_Exception &operator = (const CORBA_Exception &src);
  // Assignment operator.

  virtual ~CORBA_Exception (void);
  // Destructor.

  // = To throw the exception (when using the standard mapping).
  virtual void _raise (void) = 0;

  // = The static narrow operation.
  static CORBA_Exception *_downcast (CORBA_Exception *x);

  // = These are TAO-specific extensions.

  const char *_id (void) const;
  // Return the repository ID of the Exception.

  virtual CORBA::TypeCode_ptr _type (void) const;
  // Will be overridden in the concrete derived classes.

  // = To implement the narrow method.
  virtual int _is_a (const char* repository_id) const;

  CORBA_Exception (const char* repository_id);
  // Constructor from a respository id.

  void _tao_print_exception (const char *info,
                             FILE *f = stdout) const;
  // Print the exception <ex> to output determined by <f>.  This
  // function is not CORBA compliant.

  const char *_info (void) const;
  // Returns a string containing information about the exception. This
  // function is not CORBA compliant.

  virtual void _tao_encode (TAO_OutputCDR &cdr,
                            CORBA::Environment &) const = 0;
  virtual void _tao_decode (TAO_InputCDR &cdr,
                            CORBA::Environment &) = 0;

  static void _tao_any_destructor (void *);
  // Used in the non-copying Any insertion operator.

  // = Methods required for memory management support.
  CORBA::ULong _incr_refcnt (void);
  CORBA::ULong _decr_refcnt (void);

protected:
  CORBA_Exception (void);
  // Default constructor is protected.

private:
  char *id_;
  // Storage of our repository id.

  CORBA::ULong refcount_;
  // Reference count to avoid copying overhead.

  ACE_SYNCH_MUTEX refcount_lock_;
  // Mutex to protect the reference count; though in most cases this
  // class is used only in one thread adding a mutex here is *not*
  // expensive, because uses of this class should never be on the
  // critical path.
};

#if !defined (ACE_LACKS_IOSTREAM_TOTALLY)

// Convenient ostream operator.
TAO_Export ostream& operator<< (ostream &os,
                                const CORBA_Exception &e);

#endif // (ACE_LACKS_IOSTREAM_TOTALLY)

class TAO_Export CORBA_UserException : public CORBA_Exception
{
  // = TITLE
  //   User exceptions are those defined by application developers
  //   using OMG-IDL.
public:
  // = Initialization and termination methods.

  CORBA_UserException (const CORBA_UserException &src);
  // Copy ctor.

  ~CORBA_UserException (void);
  // Destructor.

  CORBA_UserException &operator= (const CORBA_UserException &src);
  // Assignment operator.

  static CORBA_UserException *_downcast (CORBA_Exception *exception);
  // The narrow operation.

  // = TAO specific extension.

  CORBA_UserException (const char* repository_id);
  // Constructor from a repository id.

  virtual int _is_a (const char *interface_id) const;
  // Used for narrowing

  //protected:
  CORBA_UserException (void);
  // Default constructor.
};

class TAO_Export CORBA_SystemException : public CORBA_Exception
{
  // = TITLE
  //   CORBA_SystemException
  //
  // = DESCRIPTION
  //   System exceptions are those defined in the CORBA spec; OMG-IDL
  //   defines these.
public:
  // = Initialization and termination methods.

  CORBA_SystemException (void);
  // Default Ctor

  CORBA_SystemException (const CORBA_SystemException &src);
  // Copy ctor.

  ~CORBA_SystemException (void);
  // Destructor.

  CORBA_SystemException &operator= (const CORBA_SystemException &src);
  // Assignment operator.

  CORBA::ULong minor (void) const;
  // Get the minor status.

  void minor (CORBA::ULong m);
  // Set the minor status.

  CORBA::CompletionStatus completed (void) const;
  // Get the completion status.

  void completed (CORBA::CompletionStatus c);
  // Set the operation completion status.

  static CORBA_SystemException *_downcast (CORBA_Exception *exception);
  // Narrow to a SystemException.

  // = TAO-specific extension.

  virtual int _is_a (const char *type_id) const;
  // Helper for the _downcast operation.

  void _tao_print_system_exception (FILE *f = stdout) const;
  // Print the system exception <ex> to output determined by f.  This
  // function is not CORBA compliant.

  const char *_info (void) const;
  // Returns a string containing information about the exception. This
  // function is not CORBA compliant.

  virtual void _tao_encode (TAO_OutputCDR &cdr,
                            CORBA::Environment &) const;
  virtual void _tao_decode (TAO_InputCDR &cdr,
                            CORBA::Environment &);

  static CORBA::ULong _tao_minor_code (u_int location,
                                       int errno_value);
  // Helper to create a minor status value.

  static CORBA::ULong _tao_errno (int errno_value);
  // Helper to translate a platform-specific errno to a TAO errno
  // value.

protected:
  CORBA_SystemException (const char *repository_id,
                         CORBA::ULong code,
                         CORBA::CompletionStatus completed);
  // Ctor using a repository id.

private:
  CORBA::ULong minor_;
  // Minor code.

  CORBA::CompletionStatus completed_;
  // Completion status.
};

// Declarations for all of the CORBA standard exceptions.
//
// @@ - shouldn't have a default minor code, at least for code that's
// inside the ORB.  All minor codes should be symbolically catalogued.

#define TAO_SYSTEM_EXCEPTION(name) \
class TAO_Export CORBA_ ## name : public CORBA_SystemException { \
public: \
  CORBA_ ## name (void); \
  CORBA_ ## name (CORBA::ULong code, \
                  CORBA::CompletionStatus completed) \
    : CORBA_SystemException ("IDL:omg.org/CORBA/" #name ":1.0", code, completed) \
    { } \
  static CORBA_##name * _downcast (CORBA_Exception* exception); \
  virtual int _is_a (const char* type_id) const; \
  virtual void _raise (void); \
  virtual CORBA::TypeCode_ptr _type (void) const; \
  static void _tao_any_destructor (void*); \
}; \
TAO_Export void operator<<= (CORBA::Any &, const CORBA_##name &); \
TAO_Export void operator<<= (CORBA::Any &, CORBA_##name *); \
TAO_Export CORBA::Boolean operator>>= (const CORBA::Any &, \
                                       const CORBA_##name *&)


TAO_SYSTEM_EXCEPTION(UNKNOWN);          // the unknown exception
TAO_SYSTEM_EXCEPTION(BAD_PARAM);        // an invalid parameter was passed
TAO_SYSTEM_EXCEPTION(NO_MEMORY);        // memory allocation failure
TAO_SYSTEM_EXCEPTION(IMP_LIMIT);        // violated implementation limit
TAO_SYSTEM_EXCEPTION(COMM_FAILURE);     // communication failure
TAO_SYSTEM_EXCEPTION(INV_OBJREF);       // invalid object reference
TAO_SYSTEM_EXCEPTION(OBJECT_NOT_EXIST); // no such object
TAO_SYSTEM_EXCEPTION(NO_PERMISSION);    // no permission for operation
TAO_SYSTEM_EXCEPTION(INTERNAL);         // ORB internal error
TAO_SYSTEM_EXCEPTION(MARSHAL);          // error marshaling param/result
TAO_SYSTEM_EXCEPTION(INITIALIZE);       // ORB initialization failure
TAO_SYSTEM_EXCEPTION(NO_IMPLEMENT);     // implementation unavailable
TAO_SYSTEM_EXCEPTION(BAD_TYPECODE);     // bad typecode
TAO_SYSTEM_EXCEPTION(BAD_OPERATION);    // invalid operation
TAO_SYSTEM_EXCEPTION(NO_RESOURCES);     // out of resources for request
TAO_SYSTEM_EXCEPTION(NO_RESPONSE);      // response not yet available
TAO_SYSTEM_EXCEPTION(PERSIST_STORE);    // persistent storage failure
TAO_SYSTEM_EXCEPTION(BAD_INV_ORDER);    // routine invocations out of order
TAO_SYSTEM_EXCEPTION(TRANSIENT);        // transient error, try again later
TAO_SYSTEM_EXCEPTION(FREE_MEM);         // cannot free memory
TAO_SYSTEM_EXCEPTION(INV_IDENT);        // invalid identifier syntax
TAO_SYSTEM_EXCEPTION(INV_FLAG);         // invalid flag was specified
TAO_SYSTEM_EXCEPTION(INTF_REPOS);       // interface repository unavailable
TAO_SYSTEM_EXCEPTION(BAD_CONTEXT);      // error processing context object
TAO_SYSTEM_EXCEPTION(OBJ_ADAPTER);      // object adapter failure
TAO_SYSTEM_EXCEPTION(DATA_CONVERSION);  // data conversion error
TAO_SYSTEM_EXCEPTION(INV_POLICY);       // invalid policies present
TAO_SYSTEM_EXCEPTION(REBIND);           // rebind needed
TAO_SYSTEM_EXCEPTION(TIMEOUT);          // operation timed out
TAO_SYSTEM_EXCEPTION(TRANSACTION_UNAVAILABLE); // no transaction
TAO_SYSTEM_EXCEPTION(TRANSACTION_MODE);        // invalid transaction mode
TAO_SYSTEM_EXCEPTION(TRANSACTION_REQUIRED);    // operation needs transaction
TAO_SYSTEM_EXCEPTION(TRANSACTION_ROLLEDBACK);  // operation was a no-op
TAO_SYSTEM_EXCEPTION(INVALID_TRANSACTION);     // invalid TP context passed

#undef TAO_SYSTEM_EXCEPTION

class TAO_Export CORBA_UnknownUserException : public CORBA_UserException
{
  // = TITLE
  //   CORBA_UnknownUserException
  //
  // = DESCRIPTION
  //   When user exceptions are received by a DII invocation the ORB
  //   is unable to create the exception with the right dynamic type;
  //   to workaround this problem it throws a
  //   <CORBA::UnknownUserException> that contains the exception inside
  //   an Any.
public:
  // = Initialization and termination methods.
  CORBA_UnknownUserException (void);
  // Constructor.

  CORBA_UnknownUserException (CORBA_Any& exception);
  // Destructor.

  CORBA_UnknownUserException (const CORBA_UnknownUserException& e);
  // Copy constructor

  virtual ~CORBA_UnknownUserException (void);
  // Constructor.

  CORBA_Any& exception (void);
  // Return the any containing the user exception.

  virtual void _raise (void);
  // To throw an UnknownUserException of this type.

  virtual void _tao_encode (TAO_OutputCDR &cdr,
                            CORBA::Environment &) const;
  virtual void _tao_decode (TAO_InputCDR &cdr,
                            CORBA::Environment &);

  static CORBA_UnknownUserException *_downcast (CORBA_Exception *ex);
  // Narrow to an UnknowUserException

  // = TAO specific extension.

  virtual int _is_a (const char *type_id) const;
  // Helper method to implement _downcast.

  virtual CORBA::TypeCode_ptr _type (void) const;
  // This class has a specific typecode.

private:
  CORBA_Any *exception_;
  // Holder for the actual exception.
};

class TAO_Export TAO_Exceptions
{
  // = TITLE
  //   This class is a namespace for exception-related static data and
  //   methods.
public:
  static void make_standard_typecode (CORBA::TypeCode_ptr &tcp,
                                      const char *name,
                                      char *buf,
                                      size_t buflen,
                                      CORBA_Environment &ACE_TRY_ENV =
                                      TAO_default_environment ());
  // Make the TypeCode for a standard exception.  When used correctly,
  // initializing system exceptions is only an exercise in CPU time;
  // it allocates no new memory.

  static void make_unknown_user_typecode (CORBA::TypeCode_ptr &tcp,
                                          CORBA_Environment &ACE_TRY_ENV =
                                          TAO_default_environment ());
  // Make the TypeCode for the CORBA::UnknownUserException standard
  // exception.

  static void init (CORBA_Environment &ACE_TRY_ENV =
                    TAO_default_environment ());
  // Runtime initialization of all standard exception typecodes.
  // Called from <CORBA::ORB_init>.

  static void fini (void);
  // Runtime finalization of all standard exception typecodes.

  static CORBA_SystemException *
       create_system_exception (const char *id,
                                CORBA_Environment &ACE_TRY_ENV =
                                    TAO_default_environment ());
  // Create a CORBA::SystemException given the interface repository
  // ID.

  static CORBA::ExceptionList *system_exceptions;
  // List of system exceptions.

private:
  static ACE_Allocator *global_allocator_;
  // This global allocator is used to initialize system exception
  // typecodes.  Since at the time, the ORB is mostly still not
  // available.  Using a separate allocator prevent CDR routine from
  // accessing the optimized allocators from the ORB.

  static int initialized_;
  // Flag that denotes that the TAO's CORBA exceptions have been
  // initialized.
};

class CORBA_ExceptionList;
typedef CORBA_ExceptionList *CORBA_ExceptionList_ptr;

class TAO_Export CORBA_ExceptionList
{
  // = TITLE
  //   ExceptionList definition taken from CORBA v2.2 Feb 1998
  //
  // = DESCRIPTION
  //   Maintains a list of TypeCodes for Exceptions.
public:
  // = Intialization and termination methods.

  CORBA_ExceptionList (void);
  // constructor

  CORBA_ExceptionList (CORBA::ULong len,
                       CORBA::TypeCode_ptr *tc_list);
  // Constructor - initialize given a length and an array of
  // TypeCodes.

  ~CORBA_ExceptionList (void);
  // Destructor.

  CORBA::ULong count ();
  // Return the number of elements.

  CORBA_ExceptionList_ptr _duplicate (void);
  // Increase the reference count.

  static CORBA_ExceptionList_ptr _duplicate (CORBA_ExceptionList *);
  // Increase the reference count in the spec defined manner.

  void _destroy (void);

  static CORBA_ExceptionList_ptr _nil (void);

  void add (CORBA::TypeCode_ptr tc);
  // Add a TypeCode to the list

  void add_consume (CORBA::TypeCode_ptr tc);
  // Add and consume a TypeCode to the list

  CORBA::TypeCode_ptr item (CORBA::ULong slot,
                            CORBA_Environment &ACE_TRY_ENV =
                            TAO_default_environment ());
  // Return the typecode at slot i. Raises the "Bounds" exception.

  void remove (CORBA::ULong slot,
               CORBA_Environment &ACE_TRY_ENV =
               TAO_default_environment ());
  // Remove the typecode at slot i. Raises the "Bounds" exception.

  void  _incr_refcnt (void);
  void  _decr_refcnt (void);
  // Increment and decrement ref counts

#if !defined(__GNUC__) || __GNUC__ > 2 || __GNUC_MINOR__ >= 8
  typedef CORBA::ExceptionList_ptr _ptr_type;
  typedef CORBA::ExceptionList_var _var_type;
#endif /* __GNUC__ */
  // Useful for template programming.

private:
  // = Not allowed.
  CORBA_ExceptionList (const CORBA_ExceptionList &);
  CORBA_ExceptionList &operator= (const CORBA_ExceptionList &);

  ACE_Atomic_Op<ACE_SYNCH_MUTEX, CORBA::ULong> ref_count_;
  // Reference counter.

  ACE_Unbounded_Queue<CORBA::TypeCode_ptr> tc_list_;
  // internal list of typecodes
};

class TAO_Export CORBA_ExceptionList_var
{
  // = TITLE
  //   CORBA_ExceptionList_var
  //
  // = DESCRIPTION
  //   Lifecycle management helper class for ExceptionList objects.
public:
  CORBA_ExceptionList_var (void);
  // default constructor
  CORBA_ExceptionList_var (CORBA_ExceptionList_ptr);
  CORBA_ExceptionList_var (const CORBA_ExceptionList_var &);
  // copy constructor
  ~CORBA_ExceptionList_var (void);
  // destructor

  CORBA_ExceptionList_var &operator= (CORBA_ExceptionList_ptr);
  CORBA_ExceptionList_var &operator= (const CORBA_ExceptionList_var &);
  CORBA_ExceptionList_ptr operator-> (void) const;

  operator const CORBA_ExceptionList_ptr &() const;
  operator CORBA_ExceptionList_ptr &();
  // in, inout, out, _retn
  CORBA_ExceptionList_ptr in (void) const;
  CORBA_ExceptionList_ptr &inout (void);
  CORBA_ExceptionList_ptr &out (void);
  CORBA_ExceptionList_ptr _retn (void);
  CORBA_ExceptionList_ptr ptr (void) const;

private:
  CORBA_ExceptionList_ptr ptr_;
};

#if defined (TAO_DONT_CATCH_DOT_DOT_DOT)
class TAO_Export TAO_DONT_CATCH
{
  // = TITLE
  //   This class is only used internally in TAO as an exception
  //   that never gets thrown.  Never use this class anywhere.
public:
  TAO_DONT_CATCH (void);
};
#endif /* TAO_DONT_CATCH_DOT_DOT_DOT */

#if defined (__ACE_INLINE__)
# include "tao/Exception.i"
#endif /* __ACE_INLINE__ */

#include "ace/post.h"
#endif /* TAO_EXCEPTION_H */
