/* $Id$
 * This code was generated by the XML Schema Compiler.
 *
 * Changes made to this code will most likely be overwritten
 * when the handlers are recompiled.
 *
 * If you find errors or feel that there are bugfixes to be made,
 * please contact the current XSC maintainer:
 *             Will Otte <wotte@dre.vanderbilt.edu>
 */

// Fix for Borland compilers, which seem to have a broken
// <string> include.
#ifdef __BORLANDC__
# include <string.h>
#endif

#include "cpd.hpp"

namespace CIAO
{
  namespace Config_Handlers
  {
    // PackagedComponentImplementation
    // 

    PackagedComponentImplementation::
    PackagedComponentImplementation (::XMLSchema::string< ACE_TCHAR > const& name__,
                                     ::CIAO::Config_Handlers::ComponentImplementationDescription const& referencedImplementation__)
    : 
    ::XSCRT::Type (), 
    name_ (new ::XMLSchema::string< ACE_TCHAR > (name__)),
    referencedImplementation_ (new ::CIAO::Config_Handlers::ComponentImplementationDescription (referencedImplementation__)),
    regulator__ ()
    {
      name_->container (this);
      referencedImplementation_->container (this);
    }

    PackagedComponentImplementation::
    PackagedComponentImplementation (PackagedComponentImplementation const& s)
    :
    ::XSCRT::Type (),
    name_ (new ::XMLSchema::string< ACE_TCHAR > (*s.name_)),
    referencedImplementation_ (new ::CIAO::Config_Handlers::ComponentImplementationDescription (*s.referencedImplementation_)),
    regulator__ ()
    {
      name_->container (this);
      referencedImplementation_->container (this);
    }

    PackagedComponentImplementation& PackagedComponentImplementation::
    operator= (PackagedComponentImplementation const& s)
    {
      name (*s.name_);

      referencedImplementation (*s.referencedImplementation_);

      return *this;
    }


    // PackagedComponentImplementation
    // 
    ::XMLSchema::string< ACE_TCHAR > const& PackagedComponentImplementation::
    name () const
    {
      return *name_;
    }

    void PackagedComponentImplementation::
    name (::XMLSchema::string< ACE_TCHAR > const& e)
    {
      *name_ = e;
    }

    // PackagedComponentImplementation
    // 
    ::CIAO::Config_Handlers::ComponentImplementationDescription const& PackagedComponentImplementation::
    referencedImplementation () const
    {
      return *referencedImplementation_;
    }

    void PackagedComponentImplementation::
    referencedImplementation (::CIAO::Config_Handlers::ComponentImplementationDescription const& e)
    {
      *referencedImplementation_ = e;
    }


    // ComponentPackageDescription
    // 

    ComponentPackageDescription::
    ComponentPackageDescription ()
    : 
    regulator__ ()
    {
    }

    ComponentPackageDescription::
    ComponentPackageDescription (ComponentPackageDescription const& s)
    :
    ::XSCRT::Type (),
    label_ (s.label_.get () ? new ::XMLSchema::string< ACE_TCHAR > (*s.label_) : 0),
    UUID_ (s.UUID_.get () ? new ::XMLSchema::string< ACE_TCHAR > (*s.UUID_) : 0),
    realizes_ (s.realizes_.get () ? new ::CIAO::Config_Handlers::ComponentInterfaceDescription (*s.realizes_) : 0),
    configProperty_ (s.configProperty_),
    implementation_ (s.implementation_),
    infoProperty_ (s.infoProperty_),
    contentLocation_ (s.contentLocation_.get () ? new ::XMLSchema::string< ACE_TCHAR > (*s.contentLocation_) : 0),
    href_ (s.href_.get () ? new ::XMLSchema::string< ACE_TCHAR > (*s.href_) : 0),
    regulator__ ()
    {
      if (label_.get ()) label_->container (this);
      if (UUID_.get ()) UUID_->container (this);
      if (realizes_.get ()) realizes_->container (this);
      if (contentLocation_.get ()) contentLocation_->container (this);
      if (href_.get ()) href_->container (this);
    }

    ComponentPackageDescription& ComponentPackageDescription::
    operator= (ComponentPackageDescription const& s)
    {
      if (s.label_.get ())
        label (*(s.label_));
      else
        label_.reset (0);

      if (s.UUID_.get ())
        UUID (*(s.UUID_));
      else
        UUID_.reset (0);

      if (s.realizes_.get ())
        realizes (*(s.realizes_));
      else
        realizes_.reset (0);

      configProperty_ = s.configProperty_;

      implementation_ = s.implementation_;

      infoProperty_ = s.infoProperty_;

      if (s.contentLocation_.get ())
        contentLocation (*(s.contentLocation_));
      else
        contentLocation_.reset (0);

      if (s.href_.get ()) href (*(s.href_));
      else href_ = ::std::auto_ptr< ::XMLSchema::string< ACE_TCHAR > > (0);

      return *this;
    }


    // ComponentPackageDescription
    // 
    bool ComponentPackageDescription::
    label_p () const
    {
      return label_.get () != 0;
    }

    ::XMLSchema::string< ACE_TCHAR > const& ComponentPackageDescription::
    label () const
    {
      return *label_;
    }

    void ComponentPackageDescription::
    label (::XMLSchema::string< ACE_TCHAR > const& e)
    {
      if (label_.get ())
      {
        *label_ = e;
      }

      else
      {
        label_ = ::std::auto_ptr< ::XMLSchema::string< ACE_TCHAR > > (new ::XMLSchema::string< ACE_TCHAR > (e));
        label_->container (this);
      }
    }

    // ComponentPackageDescription
    // 
    bool ComponentPackageDescription::
    UUID_p () const
    {
      return UUID_.get () != 0;
    }

    ::XMLSchema::string< ACE_TCHAR > const& ComponentPackageDescription::
    UUID () const
    {
      return *UUID_;
    }

    void ComponentPackageDescription::
    UUID (::XMLSchema::string< ACE_TCHAR > const& e)
    {
      if (UUID_.get ())
      {
        *UUID_ = e;
      }

      else
      {
        UUID_ = ::std::auto_ptr< ::XMLSchema::string< ACE_TCHAR > > (new ::XMLSchema::string< ACE_TCHAR > (e));
        UUID_->container (this);
      }
    }

    // ComponentPackageDescription
    // 
    bool ComponentPackageDescription::
    realizes_p () const
    {
      return realizes_.get () != 0;
    }

    ::CIAO::Config_Handlers::ComponentInterfaceDescription const& ComponentPackageDescription::
    realizes () const
    {
      return *realizes_;
    }

    void ComponentPackageDescription::
    realizes (::CIAO::Config_Handlers::ComponentInterfaceDescription const& e)
    {
      if (realizes_.get ())
      {
        *realizes_ = e;
      }

      else
      {
        realizes_ = ::std::auto_ptr< ::CIAO::Config_Handlers::ComponentInterfaceDescription > (new ::CIAO::Config_Handlers::ComponentInterfaceDescription (e));
        realizes_->container (this);
      }
    }

    // ComponentPackageDescription
    // 
    ComponentPackageDescription::configProperty_iterator ComponentPackageDescription::
    begin_configProperty ()
    {
      return configProperty_.begin ();
    }

    ComponentPackageDescription::configProperty_iterator ComponentPackageDescription::
    end_configProperty ()
    {
      return configProperty_.end ();
    }

    ComponentPackageDescription::configProperty_const_iterator ComponentPackageDescription::
    begin_configProperty () const
    {
      return configProperty_.begin ();
    }

    ComponentPackageDescription::configProperty_const_iterator ComponentPackageDescription::
    end_configProperty () const
    {
      return configProperty_.end ();
    }

    void ComponentPackageDescription::
    add_configProperty (::CIAO::Config_Handlers::Property const& e)
    {
      configProperty_.push_back (e);
    }

    size_t ComponentPackageDescription::
    count_configProperty(void) const
    {
      return configProperty_.size ();
    }

    // ComponentPackageDescription
    // 
    ComponentPackageDescription::implementation_iterator ComponentPackageDescription::
    begin_implementation ()
    {
      return implementation_.begin ();
    }

    ComponentPackageDescription::implementation_iterator ComponentPackageDescription::
    end_implementation ()
    {
      return implementation_.end ();
    }

    ComponentPackageDescription::implementation_const_iterator ComponentPackageDescription::
    begin_implementation () const
    {
      return implementation_.begin ();
    }

    ComponentPackageDescription::implementation_const_iterator ComponentPackageDescription::
    end_implementation () const
    {
      return implementation_.end ();
    }

    void ComponentPackageDescription::
    add_implementation (::CIAO::Config_Handlers::PackagedComponentImplementation const& e)
    {
      implementation_.push_back (e);
    }

    size_t ComponentPackageDescription::
    count_implementation(void) const
    {
      return implementation_.size ();
    }

    // ComponentPackageDescription
    // 
    ComponentPackageDescription::infoProperty_iterator ComponentPackageDescription::
    begin_infoProperty ()
    {
      return infoProperty_.begin ();
    }

    ComponentPackageDescription::infoProperty_iterator ComponentPackageDescription::
    end_infoProperty ()
    {
      return infoProperty_.end ();
    }

    ComponentPackageDescription::infoProperty_const_iterator ComponentPackageDescription::
    begin_infoProperty () const
    {
      return infoProperty_.begin ();
    }

    ComponentPackageDescription::infoProperty_const_iterator ComponentPackageDescription::
    end_infoProperty () const
    {
      return infoProperty_.end ();
    }

    void ComponentPackageDescription::
    add_infoProperty (::CIAO::Config_Handlers::Property const& e)
    {
      infoProperty_.push_back (e);
    }

    size_t ComponentPackageDescription::
    count_infoProperty(void) const
    {
      return infoProperty_.size ();
    }

    // ComponentPackageDescription
    // 
    bool ComponentPackageDescription::
    contentLocation_p () const
    {
      return contentLocation_.get () != 0;
    }

    ::XMLSchema::string< ACE_TCHAR > const& ComponentPackageDescription::
    contentLocation () const
    {
      return *contentLocation_;
    }

    void ComponentPackageDescription::
    contentLocation (::XMLSchema::string< ACE_TCHAR > const& e)
    {
      if (contentLocation_.get ())
      {
        *contentLocation_ = e;
      }

      else
      {
        contentLocation_ = ::std::auto_ptr< ::XMLSchema::string< ACE_TCHAR > > (new ::XMLSchema::string< ACE_TCHAR > (e));
        contentLocation_->container (this);
      }
    }

    // ComponentPackageDescription
    // 
    bool ComponentPackageDescription::
    href_p () const
    {
      return href_.get () != 0;
    }

    ::XMLSchema::string< ACE_TCHAR > const& ComponentPackageDescription::
    href () const
    {
      return *href_;
    }

    ::XMLSchema::string< ACE_TCHAR >& ComponentPackageDescription::
    href ()
    {
      return *href_;
    }

    void ComponentPackageDescription::
    href (::XMLSchema::string< ACE_TCHAR > const& e)
    {
      if (href_.get ())
      {
        *href_ = e;
      }

      else
      {
        href_ = ::std::auto_ptr< ::XMLSchema::string< ACE_TCHAR > > (new ::XMLSchema::string< ACE_TCHAR > (e));
        href_->container (this);
      }
    }
  }
}

namespace CIAO
{
  namespace Config_Handlers
  {
    // PackagedComponentImplementation
    //

    PackagedComponentImplementation::
    PackagedComponentImplementation (::XSCRT::XML::Element< ACE_TCHAR > const& e)
    :Base (e), regulator__ ()
    {

      ::XSCRT::Parser< ACE_TCHAR > p (e);

      while (p.more_elements ())
      {
        ::XSCRT::XML::Element< ACE_TCHAR > e (p.next_element ());
        ::std::basic_string< ACE_TCHAR > n (::XSCRT::XML::uq_name (e.name ()));

        if (n == "name")
        {
          name_ = ::std::auto_ptr< ::XMLSchema::string< ACE_TCHAR > > (new ::XMLSchema::string< ACE_TCHAR > (e));
          name_->container (this);
        }

        else if (n == "referencedImplementation")
        {
          referencedImplementation_ = ::std::auto_ptr< ::CIAO::Config_Handlers::ComponentImplementationDescription > (new ::CIAO::Config_Handlers::ComponentImplementationDescription (e));
          referencedImplementation_->container (this);
        }

        else 
        {
        }
      }
    }

    // ComponentPackageDescription
    //

    ComponentPackageDescription::
    ComponentPackageDescription (::XSCRT::XML::Element< ACE_TCHAR > const& e)
    :Base (e), regulator__ ()
    {

      ::XSCRT::Parser< ACE_TCHAR > p (e);

      while (p.more_elements ())
      {
        ::XSCRT::XML::Element< ACE_TCHAR > e (p.next_element ());
        ::std::basic_string< ACE_TCHAR > n (::XSCRT::XML::uq_name (e.name ()));

        if (n == "label")
        {
          ::XMLSchema::string< ACE_TCHAR > t (e);
          label (t);
        }

        else if (n == "UUID")
        {
          ::XMLSchema::string< ACE_TCHAR > t (e);
          UUID (t);
        }

        else if (n == "realizes")
        {
          ::CIAO::Config_Handlers::ComponentInterfaceDescription t (e);
          realizes (t);
        }

        else if (n == "configProperty")
        {
          ::CIAO::Config_Handlers::Property t (e);
          add_configProperty (t);
        }

        else if (n == "implementation")
        {
          ::CIAO::Config_Handlers::PackagedComponentImplementation t (e);
          add_implementation (t);
        }

        else if (n == "infoProperty")
        {
          ::CIAO::Config_Handlers::Property t (e);
          add_infoProperty (t);
        }

        else if (n == "contentLocation")
        {
          ::XMLSchema::string< ACE_TCHAR > t (e);
          contentLocation (t);
        }

        else 
        {
        }
      }

      while (p.more_attributes ())
      {
        ::XSCRT::XML::Attribute< ACE_TCHAR > a (p.next_attribute ());
        ::std::basic_string< ACE_TCHAR > n (::XSCRT::XML::uq_name (a.name ()));
        if (n == "href")
        {
          ::XMLSchema::string< ACE_TCHAR > t (a);
          href (t);
        }

        else 
        {
        }
      }
    }
  }
}

namespace CIAO
{
  namespace Config_Handlers
  {
  }
}

#include "XMLSchema/TypeInfo.hpp"

namespace CIAO
{
  namespace Config_Handlers
  {
    namespace
    {
      ::XMLSchema::TypeInfoInitializer < ACE_TCHAR > XMLSchemaTypeInfoInitializer_ (::XSCRT::extended_type_info_map ());

      struct PackagedComponentImplementationTypeInfoInitializer
      {
        PackagedComponentImplementationTypeInfoInitializer ()
        {
          ::XSCRT::TypeId id (typeid (::CIAO::Config_Handlers::PackagedComponentImplementation));
          ::XSCRT::ExtendedTypeInfo nf (id);

          nf.add_base (::XSCRT::ExtendedTypeInfo::Access::public_, false, typeid (::XSCRT::Type));
          ::XSCRT::extended_type_info_map ().insert (::std::make_pair (id, nf));
        }
      };

      PackagedComponentImplementationTypeInfoInitializer PackagedComponentImplementationTypeInfoInitializer_;

      struct ComponentPackageDescriptionTypeInfoInitializer
      {
        ComponentPackageDescriptionTypeInfoInitializer ()
        {
          ::XSCRT::TypeId id (typeid (::CIAO::Config_Handlers::ComponentPackageDescription));
          ::XSCRT::ExtendedTypeInfo nf (id);

          nf.add_base (::XSCRT::ExtendedTypeInfo::Access::public_, false, typeid (::XSCRT::Type));
          ::XSCRT::extended_type_info_map ().insert (::std::make_pair (id, nf));
        }
      };

      ComponentPackageDescriptionTypeInfoInitializer ComponentPackageDescriptionTypeInfoInitializer_;
    }
  }
}

namespace CIAO
{
  namespace Config_Handlers
  {
    namespace Traversal
    {
      // PackagedComponentImplementation
      //
      //

      void PackagedComponentImplementation::
      traverse (Type& o)
      {
        pre (o);
        name (o);
        referencedImplementation (o);
        post (o);
      }

      void PackagedComponentImplementation::
      traverse (Type const& o)
      {
        pre (o);
        name (o);
        referencedImplementation (o);
        post (o);
      }

      void PackagedComponentImplementation::
      pre (Type&)
      {
      }

      void PackagedComponentImplementation::
      pre (Type const&)
      {
      }

      void PackagedComponentImplementation::
      name (Type& o)
      {
        dispatch (o.name ());
      }

      void PackagedComponentImplementation::
      name (Type const& o)
      {
        dispatch (o.name ());
      }

      void PackagedComponentImplementation::
      referencedImplementation (Type& o)
      {
        dispatch (o.referencedImplementation ());
      }

      void PackagedComponentImplementation::
      referencedImplementation (Type const& o)
      {
        dispatch (o.referencedImplementation ());
      }

      void PackagedComponentImplementation::
      post (Type&)
      {
      }

      void PackagedComponentImplementation::
      post (Type const&)
      {
      }

      // ComponentPackageDescription
      //
      //

      void ComponentPackageDescription::
      traverse (Type& o)
      {
        pre (o);
        if (o.label_p ()) label (o);
        else label_none (o);
        if (o.UUID_p ()) UUID (o);
        else UUID_none (o);
        if (o.realizes_p ()) realizes (o);
        else realizes_none (o);
        configProperty (o);
        implementation (o);
        infoProperty (o);
        if (o.contentLocation_p ()) contentLocation (o);
        else contentLocation_none (o);
        if (o.href_p ()) href (o);
        else href_none (o);
        post (o);
      }

      void ComponentPackageDescription::
      traverse (Type const& o)
      {
        pre (o);
        if (o.label_p ()) label (o);
        else label_none (o);
        if (o.UUID_p ()) UUID (o);
        else UUID_none (o);
        if (o.realizes_p ()) realizes (o);
        else realizes_none (o);
        configProperty (o);
        implementation (o);
        infoProperty (o);
        if (o.contentLocation_p ()) contentLocation (o);
        else contentLocation_none (o);
        if (o.href_p ()) href (o);
        else href_none (o);
        post (o);
      }

      void ComponentPackageDescription::
      pre (Type&)
      {
      }

      void ComponentPackageDescription::
      pre (Type const&)
      {
      }

      void ComponentPackageDescription::
      label (Type& o)
      {
        dispatch (o.label ());
      }

      void ComponentPackageDescription::
      label (Type const& o)
      {
        dispatch (o.label ());
      }

      void ComponentPackageDescription::
      label_none (Type&)
      {
      }

      void ComponentPackageDescription::
      label_none (Type const&)
      {
      }

      void ComponentPackageDescription::
      UUID (Type& o)
      {
        dispatch (o.UUID ());
      }

      void ComponentPackageDescription::
      UUID (Type const& o)
      {
        dispatch (o.UUID ());
      }

      void ComponentPackageDescription::
      UUID_none (Type&)
      {
      }

      void ComponentPackageDescription::
      UUID_none (Type const&)
      {
      }

      void ComponentPackageDescription::
      realizes (Type& o)
      {
        dispatch (o.realizes ());
      }

      void ComponentPackageDescription::
      realizes (Type const& o)
      {
        dispatch (o.realizes ());
      }

      void ComponentPackageDescription::
      realizes_none (Type&)
      {
      }

      void ComponentPackageDescription::
      realizes_none (Type const&)
      {
      }

      void ComponentPackageDescription::
      configProperty (Type& o)
      {
        // VC6 anathema strikes again
        //
        ::CIAO::Config_Handlers::ComponentPackageDescription::configProperty_iterator b (o.begin_configProperty()), e (o.end_configProperty());

        if (b != e)
        {
          configProperty_pre (o);
          for (; b != e;)
          {
            dispatch (*b);
            if (++b != e) configProperty_next (o);
          }

          configProperty_post (o);
        }

        else configProperty_none (o);
      }

      void ComponentPackageDescription::
      configProperty (Type const& o)
      {
        // VC6 anathema strikes again
        //
        ::CIAO::Config_Handlers::ComponentPackageDescription::configProperty_const_iterator b (o.begin_configProperty()), e (o.end_configProperty());

        if (b != e)
        {
          configProperty_pre (o);
          for (; b != e;)
          {
            dispatch (*b);
            if (++b != e) configProperty_next (o);
          }

          configProperty_post (o);
        }

        else configProperty_none (o);
      }

      void ComponentPackageDescription::
      configProperty_pre (Type&)
      {
      }

      void ComponentPackageDescription::
      configProperty_pre (Type const&)
      {
      }

      void ComponentPackageDescription::
      configProperty_next (Type&)
      {
      }

      void ComponentPackageDescription::
      configProperty_next (Type const&)
      {
      }

      void ComponentPackageDescription::
      configProperty_post (Type&)
      {
      }

      void ComponentPackageDescription::
      configProperty_post (Type const&)
      {
      }

      void ComponentPackageDescription::
      configProperty_none (Type&)
      {
      }

      void ComponentPackageDescription::
      configProperty_none (Type const&)
      {
      }

      void ComponentPackageDescription::
      implementation (Type& o)
      {
        // VC6 anathema strikes again
        //
        ::CIAO::Config_Handlers::ComponentPackageDescription::implementation_iterator b (o.begin_implementation()), e (o.end_implementation());

        if (b != e)
        {
          implementation_pre (o);
          for (; b != e;)
          {
            dispatch (*b);
            if (++b != e) implementation_next (o);
          }

          implementation_post (o);
        }

        else implementation_none (o);
      }

      void ComponentPackageDescription::
      implementation (Type const& o)
      {
        // VC6 anathema strikes again
        //
        ::CIAO::Config_Handlers::ComponentPackageDescription::implementation_const_iterator b (o.begin_implementation()), e (o.end_implementation());

        if (b != e)
        {
          implementation_pre (o);
          for (; b != e;)
          {
            dispatch (*b);
            if (++b != e) implementation_next (o);
          }

          implementation_post (o);
        }

        else implementation_none (o);
      }

      void ComponentPackageDescription::
      implementation_pre (Type&)
      {
      }

      void ComponentPackageDescription::
      implementation_pre (Type const&)
      {
      }

      void ComponentPackageDescription::
      implementation_next (Type&)
      {
      }

      void ComponentPackageDescription::
      implementation_next (Type const&)
      {
      }

      void ComponentPackageDescription::
      implementation_post (Type&)
      {
      }

      void ComponentPackageDescription::
      implementation_post (Type const&)
      {
      }

      void ComponentPackageDescription::
      implementation_none (Type&)
      {
      }

      void ComponentPackageDescription::
      implementation_none (Type const&)
      {
      }

      void ComponentPackageDescription::
      infoProperty (Type& o)
      {
        // VC6 anathema strikes again
        //
        ::CIAO::Config_Handlers::ComponentPackageDescription::infoProperty_iterator b (o.begin_infoProperty()), e (o.end_infoProperty());

        if (b != e)
        {
          infoProperty_pre (o);
          for (; b != e;)
          {
            dispatch (*b);
            if (++b != e) infoProperty_next (o);
          }

          infoProperty_post (o);
        }

        else infoProperty_none (o);
      }

      void ComponentPackageDescription::
      infoProperty (Type const& o)
      {
        // VC6 anathema strikes again
        //
        ::CIAO::Config_Handlers::ComponentPackageDescription::infoProperty_const_iterator b (o.begin_infoProperty()), e (o.end_infoProperty());

        if (b != e)
        {
          infoProperty_pre (o);
          for (; b != e;)
          {
            dispatch (*b);
            if (++b != e) infoProperty_next (o);
          }

          infoProperty_post (o);
        }

        else infoProperty_none (o);
      }

      void ComponentPackageDescription::
      infoProperty_pre (Type&)
      {
      }

      void ComponentPackageDescription::
      infoProperty_pre (Type const&)
      {
      }

      void ComponentPackageDescription::
      infoProperty_next (Type&)
      {
      }

      void ComponentPackageDescription::
      infoProperty_next (Type const&)
      {
      }

      void ComponentPackageDescription::
      infoProperty_post (Type&)
      {
      }

      void ComponentPackageDescription::
      infoProperty_post (Type const&)
      {
      }

      void ComponentPackageDescription::
      infoProperty_none (Type&)
      {
      }

      void ComponentPackageDescription::
      infoProperty_none (Type const&)
      {
      }

      void ComponentPackageDescription::
      contentLocation (Type& o)
      {
        dispatch (o.contentLocation ());
      }

      void ComponentPackageDescription::
      contentLocation (Type const& o)
      {
        dispatch (o.contentLocation ());
      }

      void ComponentPackageDescription::
      contentLocation_none (Type&)
      {
      }

      void ComponentPackageDescription::
      contentLocation_none (Type const&)
      {
      }

      void ComponentPackageDescription::
      href (Type& o)
      {
        dispatch (o.href ());
      }

      void ComponentPackageDescription::
      href (Type const& o)
      {
        dispatch (o.href ());
      }

      void ComponentPackageDescription::
      href_none (Type&)
      {
      }

      void ComponentPackageDescription::
      href_none (Type const&)
      {
      }

      void ComponentPackageDescription::
      post (Type&)
      {
      }

      void ComponentPackageDescription::
      post (Type const&)
      {
      }
    }
  }
}

namespace CIAO
{
  namespace Config_Handlers
  {
    namespace Writer
    {
      // PackagedComponentImplementation
      //
      //

      PackagedComponentImplementation::
      PackagedComponentImplementation (::XSCRT::XML::Element< ACE_TCHAR >& e)
      : ::XSCRT::Writer< ACE_TCHAR > (e)
      {
      }

      PackagedComponentImplementation::
      PackagedComponentImplementation ()
      {
      }

      void PackagedComponentImplementation::
      traverse (Type const& o)
      {
        Traversal::PackagedComponentImplementation::traverse (o);
      }

      void PackagedComponentImplementation::
      name (Type const& o)
      {
        push_ (::XSCRT::XML::Element< ACE_TCHAR > ("name", top_ ()));
        Traversal::PackagedComponentImplementation::name (o);
        pop_ ();
      }

      void PackagedComponentImplementation::
      referencedImplementation (Type const& o)
      {
        push_ (::XSCRT::XML::Element< ACE_TCHAR > ("referencedImplementation", top_ ()));
        Traversal::PackagedComponentImplementation::referencedImplementation (o);
        pop_ ();
      }

      // ComponentPackageDescription
      //
      //

      ComponentPackageDescription::
      ComponentPackageDescription (::XSCRT::XML::Element< ACE_TCHAR >& e)
      : ::XSCRT::Writer< ACE_TCHAR > (e)
      {
      }

      ComponentPackageDescription::
      ComponentPackageDescription ()
      {
      }

      void ComponentPackageDescription::
      traverse (Type const& o)
      {
        Traversal::ComponentPackageDescription::traverse (o);
      }

      void ComponentPackageDescription::
      label (Type const& o)
      {
        push_ (::XSCRT::XML::Element< ACE_TCHAR > ("label", top_ ()));
        Traversal::ComponentPackageDescription::label (o);
        pop_ ();
      }

      void ComponentPackageDescription::
      UUID (Type const& o)
      {
        push_ (::XSCRT::XML::Element< ACE_TCHAR > ("UUID", top_ ()));
        Traversal::ComponentPackageDescription::UUID (o);
        pop_ ();
      }

      void ComponentPackageDescription::
      realizes (Type const& o)
      {
        push_ (::XSCRT::XML::Element< ACE_TCHAR > ("realizes", top_ ()));
        Traversal::ComponentPackageDescription::realizes (o);
        pop_ ();
      }

      void ComponentPackageDescription::
      configProperty_pre (Type const&)
      {
        push_ (::XSCRT::XML::Element< ACE_TCHAR > ("configProperty", top_ ()));
      }

      void ComponentPackageDescription::
      configProperty_next (Type const& o)
      {
        configProperty_post (o);
        configProperty_pre (o);
      }

      void ComponentPackageDescription::
      configProperty_post (Type const&)
      {
        pop_ ();
      }

      void ComponentPackageDescription::
      implementation_pre (Type const&)
      {
        push_ (::XSCRT::XML::Element< ACE_TCHAR > ("implementation", top_ ()));
      }

      void ComponentPackageDescription::
      implementation_next (Type const& o)
      {
        implementation_post (o);
        implementation_pre (o);
      }

      void ComponentPackageDescription::
      implementation_post (Type const&)
      {
        pop_ ();
      }

      void ComponentPackageDescription::
      infoProperty_pre (Type const&)
      {
        push_ (::XSCRT::XML::Element< ACE_TCHAR > ("infoProperty", top_ ()));
      }

      void ComponentPackageDescription::
      infoProperty_next (Type const& o)
      {
        infoProperty_post (o);
        infoProperty_pre (o);
      }

      void ComponentPackageDescription::
      infoProperty_post (Type const&)
      {
        pop_ ();
      }

      void ComponentPackageDescription::
      contentLocation (Type const& o)
      {
        push_ (::XSCRT::XML::Element< ACE_TCHAR > ("contentLocation", top_ ()));
        Traversal::ComponentPackageDescription::contentLocation (o);
        pop_ ();
      }

      void ComponentPackageDescription::
      href (Type const& o)
      {
        ::XSCRT::XML::Attribute< ACE_TCHAR > a ("href", "", top_ ());
        attr_ (&a);
        Traversal::ComponentPackageDescription::href (o);
        attr_ (0);
      }
    }
  }
}

namespace CIAO
{
  namespace Config_Handlers
  {
  }
}

