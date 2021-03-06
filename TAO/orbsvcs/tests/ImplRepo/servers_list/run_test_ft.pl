eval '(exit $?0)' && eval 'exec perl -S $0 ${1+"$@"}'
    & eval 'exec perl -S $0 $argv:q'
    if 0;

# $Id$
# -*- perl -*-

###############################################################################
use lib "$ENV{ACE_ROOT}/bin";
use PerlACE::TestTarget;

$status = 0;
$debuglevel = 0;

# Override default ping interval of 10 seconds so the test
# can run faster when showing the list of active servers
# since server is considered active is pinged within
# ping interval and ping occurs on startup.
my $ping_interval_milliseconds = 1000;

my $servers_count = 4;
my $servers_kill_count = 1;

if ($#ARGV >= 0) {
    for (my $i = 0; $i <= $#ARGV; $i++) {
	if ($ARGV[$i] eq '-debug') {
	    $debuglevel = 10;
	}
	elsif ($ARGV[$i] eq "-servers") {
	    $i++;
	    $servers_count = $ARGV[$i];
	}
	elsif ($ARGV[$i] eq "-servers_to_kill") {
	    $i++;
	    $servers_kill_count = $ARGV[$i];
	}
	else {
	    usage();
	    exit 1;
	}
    }
}

#$ENV{ACE_TEST_VERBOSE} = "1";

my $tgt_num = 0;
my $imr = PerlACE::TestTarget::create_target (++$tgt_num) || die "Create target $tgt_num failed\n";
my $replica_imr = PerlACE::TestTarget::create_target (++$tgt_num) || die "Create target $tgt_num failed\n";
my $act = PerlACE::TestTarget::create_target (++$tgt_num) || die "Create target $tgt_num failed\n";
my $ti  = PerlACE::TestTarget::create_target (++$tgt_num) || die "Create target $tgt_num failed\n";
my $srv = PerlACE::TestTarget::create_target (++$tgt_num) || die "Create target $tgt_num failed\n";

my $port = 10001 + $imr->RandomPort ();
my $rport = $port + 1;

my $objprefix = "TestObject_";

my $imriorfile = "imr_locator.ior";
my $actiorfile = "imr_activator.ior";
my $primaryiorfile = "ImR_ReplicaPrimary.ior";
my $backupiorfile = "ImR_ReplicaBackup.ior";

my $imr_imriorfile = $imr->LocalFile ($imriorfile);
my $act_imriorfile = $act->LocalFile ($imriorfile);
my $ti_imriorfile = $ti->LocalFile ($imriorfile);
my $srv_imriorfile = $srv->LocalFile ($imriorfile);
my $act_actiorfile = $act->LocalFile ($actiorfile);

my $ti_initref = "-ORBInitRef ImplRepoService=file://$ti_imriorfile";
my $act_initref = "-ORBInitRef ImplRepoService=file://$act_imriorfile";

$IMR = $imr->CreateProcess ("$ENV{TAO_ROOT}/orbsvcs/ImplRepo_Service/tao_imr_locator");
$RIMR = $replica_imr->CreateProcess ("$ENV{TAO_ROOT}/orbsvcs/ImplRepo_Service/tao_imr_locator");
$ACT = $act->CreateProcess ("$ENV{TAO_ROOT}/orbsvcs/ImplRepo_Service/tao_imr_activator");
$TI = $ti->CreateProcess ("$ENV{ACE_ROOT}/bin/tao_imr");
$SRV =  $srv->CreateProcess ("server");
my $server_cmd = $act->LocalFile ($SRV->Executable());

my $imrlogfile = "imr.log";
my $rimrlogfile = "replica_imr.log";
my $actlogfile = "act.log";
my $imr_imrlogfile = $imr->LocalFile ($imrlogfile);
my $act_actlogfile = $act->LocalFile ($actlogfile);

my $stdout_file      = "test.out";
my $stderr_file      = "test.err";
my $ti_stdout_file = $ti->LocalFile ($stdout_file);
my $ti_stderr_file = $ti->LocalFile ($stderr_file);

sub delete_files
{
    my $logs_too = shift;
    if ($logs_too == 1) {
        $imr->DeleteFile ($imrlogfile);
        $replica_imr->DeleteFile ($rimrlogfile);
        $act->DeleteFile ($actlogfile);
    }
    $imr->DeleteFile ($imriorfile);
    $replica_imr->DeleteFile ($replica_imriorfile);
    $act->DeleteFile ($imriorfile);
    $ti->DeleteFile ($imriorfile);
    $ti->DeleteFile ($replica_imriorfile);
    $srv->DeleteFile ($imriorfile);
    $act->DeleteFile ($actiorfile);

    $ti->DeleteFile ($stdout_file);
    $ti->DeleteFile ($stderr_file);

    cleanup_replication (".");

    # Remove any stray server status files caused by aborting services
    unlink <*.status>;
}

# Clean up after exit call
END
{
#    delete_files (0);
}


sub cleanup_replication
{
    my $dir = shift;
    if (!defined($dir)) {
        $dir = ".";
    }

    my $listings = "$dir/imr_listing.xml";
    my $fnd = 0;
    if (open FILE, "<$listings") {
        while (<FILE>) {
            if ($_ =~ /fname="([^"]+)"?/) {
                $fnd = 1;
                my $file = "$dir/$1";
                print "deleting $file\n" if ($debuglevel > 0);
                $imr->DeleteFile ($file);
                $imr->DeleteFile ($file . ".bak");
            }
        }
         close FILE;
    }

#   If the primary listings file has been corrupt then perform the
#   deletions from the backup file.

    if (!$fnd) {
       if (open FILE, "<$listings" . ".bak") {
           while (<FILE>) {
               if ($_ =~ /fname="([^"]+)"?/) {
                   my $file = "$dir/$1";
                   print "deleting $file\n" if ($debuglevel > 0);
                   $imr->DeleteFile ($file);
                   $imr->DeleteFile ($file . ".bak");
               }
           }
            close FILE;
       }
    }
    print "deleting $listings\n" if ($debuglevel > 0);
    $imr->DeleteFile ("$listings");
    $imr->DeleteFile ("$listings" . ".bak");
    $imr->DeleteFile ("$dir/$primaryiorfile");
    $imr->DeleteFile ("$dir/$backupiorfile");
}

sub redirect_output
{
    open(OLDOUT, ">&", \*STDOUT) or die "Can't dup STDOUT: $!";
    open(OLDERR, ">&", \*STDERR) or die "Can't dup STDERR: $!";
    open STDERR, '>', $ti_stderr_file;
    open STDOUT, '>', $ti_stdout_file;
}

sub restore_output
{
    open(STDERR, ">&OLDERR") or die "Can't dup OLDERR: $!";
    open(STDOUT, ">&OLDOUT") or die "Can't dup OLDOUT: $!";
}

sub kill_imr
{
    my $msg = shift;
    print STDERR "ERROR: $msg\n" if (length ($msg) > 0);
    $ACT->Kill (); $ACT->TimedWait (1);
    $IMR->Kill (); $IMR->TimedWait (1);
    $RIMR->Kill (); $RIMR->TimedWait (1);
    return 1;
}

sub start_imr
{
    my $debugbase = "-d $debuglevel -ORBDebugLevel $debuglevel " .
                    "-ORBVerboseLogging 1 -ORBLogFile ";
    my $actargs = "-l -o $act_actiorfile $act_initref";

    my $imrargs = " -v 1000 " .
        "--directory . --primary " .
        "-ORBListenEndpoints iiop://localhost:$port";

    my $rimrargs = " -v 1000 -o $imr_imriorfile " .
        "--directory . --backup " .
        "-ORBListenEndpoints iiop://localhost:$rport";

    if ($debuglevel > 0) {
        $imrargs .= " $debugbase $imrlogfile";
        $rimrargs .= " $debugbase $rimrlogfile";
        $actargs .= " $debugbase $actlogfile";
    }

    print "imr args = \"$imrargs\"\n" if ($debuglevel > 0);
    print "replica imr args = \"$rimrargs\"\n" if ($debuglevel > 0);
    print "act args = \"$actargs\"\n" if ($debuglevel > 0);

    $IMR->Arguments ($imrargs);
    $RIMR->Arguments ($rimrargs);
    $ACT->Arguments ($actargs);

    ##### Start ImplRepo #####
    $IMR_status = $IMR->Spawn ();
    if ($IMR_status != 0) {
        print STDERR "ERROR: ImplRepo Service returned $IMR_status\n";
        return 1;
    }
    if ($imr->WaitForFileTimed ($primaryiorfile, $imr->ProcessStartWaitInterval()) == -1) {
        print STDERR "ERROR: cannot find file <$primaryiorfile>\n";
        $IMR->Kill (); $IMR->TimedWait (1);
        return 1;
    }

    $IMR_status = $RIMR->Spawn ();
    if ($IMR_status != 0) {
        print STDERR "ERROR: replica ImplRepo Service returned $IMR_status\n";
        $IMR->Kill (); $IMR->TimedWait (1);
        return 1;
    }
    if ($imr->WaitForFileTimed ($imriorfile, $imr->ProcessStartWaitInterval()) == -1) {
        print STDERR "ERROR: cannot find file <$imr_imriorfile>\n";
        $IMR->Kill (); $IMR->TimedWait (1);
        $RIMR->Kill (); $RIMR->TimedWait (1);
        return 1;
    }

    if ($imr->GetFile ($imriorfile) == -1) {
        print STDERR "ERROR: cannot retrieve file <$imr_imriorfile>\n";
        $IMR->Kill (); $IMR->TimedWait (1);
        $RIMR->Kill (); $RIMR->TimedWait (1);
        return 1;
    }
    if ($act->PutFile ($imriorfile) == -1) {
        print STDERR "ERROR: cannot set file <$act_imriorfile>\n";
        $IMR->Kill (); $IMR->TimedWait (1);
        $RIMR->Kill (); $RIMR->TimedWait (1);
        return 1;
    }
    if ($ti->PutFile ($imriorfile) == -1) {
        print STDERR "ERROR: cannot set file <$ti_imriorfile>\n";
        $IMR->Kill (); $IMR->TimedWait (1);
        $RIMR->Kill (); $RIMR->TimedWait (1);
        return 1;
    }
    if ($srv->PutFile ($imriorfile) == -1) {
        print STDERR "ERROR: cannot set file <$srv_imriorfile>\n";
        $IMR->Kill (); $IMR->TimedWait (1);
        $RIMR->Kill (); $RIMR->TimedWait (1);
        return 1;
    }

    $ACT_status = $ACT->Spawn ();
    if ($ACT_status != 0) {
        print STDERR "ERROR: ImR Activator returned $ACT_status\n";
        return 1;
    }
    if ($act->WaitForFileTimed ($actiorfile,$act->ProcessStartWaitInterval()) == -1) {
        return kill_imr ("cannot find file <$act_imriorfile>");
    }


}

sub do_ti_command
{
    my $start = shift;
    my $end = shift;
    my $delstat = shift;
    my $cmd = shift;
    my $cmdargs1 = shift;
    my $cmdargs2 = shift;

    for(my $i = $start; $i < $end; $i++) {
        my $obj_name = $objprefix . "$i";
        if ($delstat != 0) {
            my $status_file_name = $obj_name . ".status";
            $srv->DeleteFile ($status_file_name);
        }
        my $cmdargs = $cmdargs1;
        $cmdargs .= "$i $cmdargs2" if (length ($cmdargs2) > 0);
        print "invoking ti cmd $cmd $obj_name $cmdargs\n" if ($debuglevel > 0);
        $TI->Arguments ("$ti_initref $cmd $obj_name $cmdargs");
        $TI_status = $TI->SpawnWaitKill ($ti->ProcessStartWaitInterval());
        if ($TI_status != 0) {
            return kill_imr ("tao_imr $cmd $obj_name returned $TI_status");
        }
    }
}

sub list_active_servers
{
    my $list_options = shift;
    my $start_time = time();
    $TI->Arguments ("$ti_initref list $list_options");
    # Redirect output so we can count number of lines in output
    redirect_output();
    $TI_status = $TI->SpawnWaitKill ($ti->ProcessStartWaitInterval());
    my $list_time = time() - $start_time;
    restore_output();
    if ($TI_status != 0) {
        kill_imr ("tao_imr list returned $TI_status");
        return -1;
    }
    open (FILE, $stderr_file) or die "Can't open $stderr_file: $!";
    $active_servers = 0;
    while (<FILE>) {
	print STDERR $_;
	$active_servers++;
    }
    close FILE;
    print STDERR "List took $list_time seconds.\n";
    return $active_servers;
}

sub servers_list_test
{
    print "Running FT active server list test with $servers_count servers.\n";

    my $result = 0;
    my $start_time = time();

    if (start_imr () != 0) {
        return 1;
    }

    if (do_ti_command (0, $servers_count, 1, "add",
                       "-c \"$server_cmd -ORBUseIMR 1 -n ",
                       "$act_initref\"") != 0) {
        return 1;
    }

    if (do_ti_command (0, $servers_count, 0, "start") != 0) {
        return 1;
    }

    print "\nKilling $servers_kill_count servers\n";
    if (do_ti_command (0, $servers_kill_count, 1, "shutdown", "") != 0) {
        return 1;
    }

    print "\nList of active servers from primary\n";
    $active_servers_before_kill = list_active_servers("-a");
    if ($active_servers_before_kill < 0) {
        return 1;
    }
    print "\nKilling primary IMR Locator\n";
    $IMR->Kill (); $IMR->TimedWait (1);
    sleep (2);

    print "\nList of active servers from backup\n";
    $active_servers_after_kill = list_active_servers("-a");
    if ($active_servers_after_kill < 0) {
        return 1;
    }

    if ($active_servers_after_kill != $active_servers_before_kill) {
	print STDERR
	    "ERROR: Excepted list of active servers after killing ".
	    "a server to be " . ($active_servers_before_kill) .
	    " but was $active_servers_after_kill\n";
	$status = 1;
    }

    print "\nList of servers registered with the ImR after killing a server\n";
    list_active_servers("");

    print "\n";

    if (do_ti_command ($servers_kill_count, $servers_count, 1, "shutdown", "") != 0) {
        return 1;
    }

    kill_imr ("");

    my $test_time = time() - $start_time;

    print "\nFinished. The test took $test_time seconds.\n";

    return $status;
}

sub usage() {
    print "Usage: run_test_ft.pl ".
	"[-servers <num=$servers_count>] ".
	"[-servers_to_kill <num=$servers_kill_count>] \n";
}

###############################################################################
###############################################################################

delete_files (1);

my $ret = servers_list_test();

exit $ret;
