/**
 * @file EM_Launcher.h
 * @author William R. Otte <wotte@dre.vanderbilt.edu>
 *
 * $Id$
 *
 * Plan Launcher bridge for the Execution Manager.
 */

#ifndef DANCE_PLAN_LAUNCHER_EM
#define DANCE_PLAN_LAUNCHER_EM

#include "Plan_Launcher_Base_Impl_T.h"

#include "dance/Deployment/Deployment_DomainApplicationC.h"
#include "dance/Deployment/Deployment_DomainApplicationManagerC.h"
#include "dance/Deployment/Deployment_ExecutionManagerC.h"
#include "dance/Plan_Launcher/Plan_Launcher_Export.h"

namespace DAnCE
{
  class DAnCE_Plan_Launcher_Export EM_Launcher :
    public virtual Plan_Launcher_Base_Impl< ::Deployment::ExecutionManager,
                                            ::Deployment::DomainApplicationManager,
                                            ::Deployment::DomainApplication >
  {
    typedef Plan_Launcher_Base_Impl< ::Deployment::ExecutionManager,
                                     ::Deployment::DomainApplicationManager,
                                     ::Deployment::DomainApplication > __Base;

  public:
    EM_Launcher (CORBA::ORB_ptr orb,
                      __Base::Manager_ptr managerw);

    ~EM_Launcher (void);


    bool lookup_by_uuid (const char *uuid,
                         CORBA::Object_out am,
                         CORBA::Object_out app);
  };
}

#endif
