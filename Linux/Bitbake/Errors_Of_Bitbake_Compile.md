1、先加编译命令路径：
用叠加：export PATH=/home/chunyun/yocto/bitbake/bin/:$PATH
如果直接写：export PATH=/home/chunyun/yocto/bitbake/bin/
 path路径直接变成了bitbake执行路径，其他sh命令就不能用了，比如cd、vim等。

2、编译时候：bitbake firstrecipe -vDD

这样能看到每一步的步骤是什么。哪里出错。好改正。

3、ERROR: no recipe files to build, check your BBPATH and BBFILES?  
没有设置BBPATH或者BBFILES的路径。
可以使用以下两种之一的方法。
方法a、直接用export设置：
BBPATH="projectdirectory"
     $ export BBPATH
我的projectdirectory是 /home/chunyun/yocto/bitbake/

方法b、在conf/bblayers.conf 设置。
内容如下；
BBPATH := "${TOPDIR}"  
BBFILES ?= ""  
BBLAYERS = " \  
  ${TOPDIR}/meta-test \  
    "
4、WARNING: No bb files matched BBFILE_PATTERN_test '^/home/chunyun/yocto/hello/meta-test/'

这个是没有找到BBFILE_PATTERN_test的路径。主要是设置BBFILE的路径。
如3所示。
方法a、直接export设置
BBPATH="projectdirectory"
     $ export BBPATH
方法b、修改 mete-test/conf/layer.conf

BBPATH .= ":${LAYERDIR}"  
BBFILES += "${LAYERDIR}/recipes-*/*/*.bb \  
            ${LAYERDIR}/recipes-*/*/*.bbappend"  
BBFILE_COLLECTIONS += "test"  
BBFILE_PATTERN_test := "^${LAYERDIR}/"  
BBFILE_PRIORITY_test = "5"

其中meta-test是我的layer路径。

5、错误显示
IOError: file conf/bitbake.conf not found in /home/chunyun/yocto/hello

ERROR: Unable to parse conf/bitbake.conf: file conf/bitbake.conf not found in /home/chunyun/yocto/hello
这个是没有找到bitbake.conf文件。
在hello目录下编辑conf/bitbake.conf 文件，内容如下：
TMPDIR  = "${TOPDIR}/tmp"  
CACHE   = "${TMPDIR}/cache"  
STAMP   = "${TMPDIR}/stamps"  
T       = "${TMPDIR}/work"  
B       = "${TMPDIR}"  

这个文件是基本配置文件，用来指定输出的路径的。

6、错误显示
ParseError: ParseError in configuration INHERITs: Could not inherit file classes/base.bbclass

ERROR: Unable to parse base: ParseError in configuration INHERITs: Could not inherit file classes/base.bbclass
这个是说明没有配置class类文件。

可以直接在hello目录下建立一个classes目录，编辑一个classes/base.bbclass 文件，内容如下：
addtask build

7、错误显示 
Nothing to do.  Use 'bitbake world' to build everything, or run 'bitbake --help' for usage information.
这个表明是没有layer文件，没有执行任何的操作。
我们需要连接一个layer文件，这个是根据执行的目标环境而设定的。我的操作是在hello目录下建立一个meta-test目录
mkdir meta-test
进入meta-test目录，添加一个conf文件夹，再加入一个layer.conf文件。

内容如下如5 中所示。

需要说明的是：
BBFILES += "${LAYERDIR}/recipes-*/*/*.bb \  
            ${LAYERDIR}/recipes-*/*/*.bbappend"  

这个目录是我自己加入的，如果需要的话主动加入自己所要执行的.bb和.bbappend文件路径。

8、错误显示
Parsing recipes: 100% |###############################################################################################| Time: 00:00:00  
Parsing of 1 .bb files complete (0 cached, 1 parsed). 1 targets, 0 skipped, 0 masked, 0 errors.  
DEBUG: parsing complete  
ERROR: Nothing PROVIDES 'firstrecipe'  
这个是我自己执行：bitbake firstecipe没有指明具体执行的firstrecipe_0.0.bb的方法名称。PN，
参考http://www.yoctoproject.org/docs/1.8/bitbake-user-manual/bitbake-user-manual.html#var-PN
修改为：
PN = 'firstrecipe'  
PV = '1'  



成功执行：
Parsing recipes: 100% |###############################################################################################| Time: 00:00:00  
Parsing of 1 .bb files complete (0 cached, 1 parsed). 1 targets, 0 skipped, 0 masked, 0 errors.  
NOTE: Resolving any missing task queue dependencies  
NOTE: Preparing RunQueue  
NOTE: Executing RunQueue Tasks  
NOTE: Tasks Summary: Attempted 7 tasks of which 7 didn't need to be rerun and all succeeded.  


这个是具体执行步骤： bitbake firstrecipe   （firstrecipe 的是我的执行的方法）

DEBUG: Removed the following variables from the environment: LC_NUMERIC, MANDATORY_PATH, XDG_GREETER_DATA_DIR, GNOME_DESKTOP_SESSION_ID, LC_IDENTIFICATION, LESSOPEN, XDG_VTNR, QT_IM_MODULE, XDG_SEAT, LC_PAPER, GNOME_KEYRING_CONTROL, DISPLAY, LANG, XDG_SESSION_PATH, XAUTHORITY, LANGUAGE, SESSION_MANAGER, LC_MONETARY, QT_QPA_PLATFORMTHEME, CLUTTER_IM_MODULE, TEXTDOMAIN, JOB, WINDOWID, SESSIONTYPE, XMODIFIERS, GPG_AGENT_INFO, QT4_IM_MODULE, SELINUX_INIT, SSH_AUTH_SOCK, XDG_RUNTIME_DIR, INSTANCE, LC_ADDRESS, COMPIZ_CONFIG_PROFILE, COMPIZ_BIN_PATH, SESSION, VTE_VERSION, BBFILES, GDMSESSION, IM_CONFIG_PHASE, TEXTDOMAINDIR, XDG_DATA_DIRS, XDG_SEAT_PATH, XDG_CONFIG_DIRS, XDG_CURRENT_DESKTOP, XDG_SESSION_ID, DBUS_SESSION_BUS_ADDRESS, _, DEFAULTS_PATH, GTK_IM_MODULE, DESKTOP_SESSION, UPSTART_SESSION, LESSCLOSE, GNOME_KEYRING_PID, OLDPWD, GDM_LANG, LC_TELEPHONE, GTK_MODULES, LC_MEASUREMENT, SHLVL, COLORTERM, LC_NAME, XDG_MENU_PREFIX, LC_TIME, LS_COLORS  
DEBUG: Found bblayers.conf (/home/chunyun/yocto/hello/conf/bblayers.conf)  
DEBUG: Adding layer /home/chunyun/yocto/hello/meta-test  
DEBUG: Inheriting /home/chunyun/yocto/hello/classes/base.bbclass (from configuration INHERITs:0)  
DEBUG: Inheriting /home/chunyun/yocto/hello/classes/logging.bbclass (from /home/chunyun/yocto/hello/classes/base.bbclass:3)  
DEBUG: Clearing SRCREV cache due to cache policy of: clear  
DEBUG: Using cache in '/home/chunyun/yocto/hello/tmp/cache/local_file_checksum_cache.dat'  
DEBUG: Using cache in '/home/chunyun/yocto/hello/tmp/cache/bb_codeparser.dat'  
DEBUG: Features set [3] (was [3])  
DEBUG: collecting .bb files  
DEBUG: Using cache in '/home/chunyun/yocto/hello/tmp/cache'  
DEBUG: Cache: /home/chunyun/yocto/hello/meta-test/recipes-example/firstrecipe/firstrecipe_0.0.bb is not cached  
Parsing recipes: 100% |###############################################################################################| Time: 00:00:00  
Parsing of 1 .bb files complete (0 cached, 1 parsed). 1 targets, 0 skipped, 0 masked, 0 errors.  
DEBUG: parsing complete  
DEBUG: providers for firstrecipe are: ['firstrecipe']  
DEBUG: sorted providers for firstrecipe are: ['/home/chunyun/yocto/hello/meta-test/recipes-example/firstrecipe/firstrecipe_0.0.bb']  
DEBUG: adding /home/chunyun/yocto/hello/meta-test/recipes-example/firstrecipe/firstrecipe_0.0.bb to satisfy firstrecipe  
DEBUG: Added dependencies [] for /home/chunyun/yocto/hello/meta-test/recipes-example/firstrecipe/firstrecipe_0.0.bb  
NOTE: Resolving any missing task queue dependencies  
DEBUG: Resolved 0 extra dependencies  
NOTE: Preparing RunQueue  
NOTE: Marking Active Tasks  
NOTE: Pruned 0 inactive tasks, 7 left  
NOTE: Assign Weightings  
NOTE: Compute totals (have 1 endpoint(s))  
DEBUG: Starting bitbake-worker  
NOTE: Executing RunQueue Tasks  
DEBUG: Considering 0 (/home/chunyun/yocto/hello/meta-test/recipes-example/firstrecipe/firstrecipe_0.0.bb, do_fetch): set([1])  
DEBUG: Considering 1 (/home/chunyun/yocto/hello/meta-test/recipes-example/firstrecipe/firstrecipe_0.0.bb, do_unpack): set([2])  
DEBUG: Considering 2 (/home/chunyun/yocto/hello/meta-test/recipes-example/firstrecipe/firstrecipe_0.0.bb, do_patch): set([3])  
DEBUG: Considering 3 (/home/chunyun/yocto/hello/meta-test/recipes-example/firstrecipe/firstrecipe_0.0.bb, do_configure): set([4])  
DEBUG: Considering 4 (/home/chunyun/yocto/hello/meta-test/recipes-example/firstrecipe/firstrecipe_0.0.bb, do_make): set([5])  
DEBUG: Considering 5 (/home/chunyun/yocto/hello/meta-test/recipes-example/firstrecipe/firstrecipe_0.0.bb, do_install): set([6])  
DEBUG: Considering 6 (/home/chunyun/yocto/hello/meta-test/recipes-example/firstrecipe/firstrecipe_0.0.bb, do_build): set([])  
DEBUG: Skip list (pre setsceneverify) []  
DEBUG: Full skip list set([])  
DEBUG: Using runqueue scheduler 'speed'  
DEBUG: Stamp current task 0 (/home/chunyun/yocto/hello/meta-test/recipes-example/firstrecipe/firstrecipe_0.0.bb, do_fetch)  
DEBUG: Marking task 1 (/home/chunyun/yocto/hello/meta-test/recipes-example/firstrecipe/firstrecipe_0.0.bb, do_unpack) as buildable  
DEBUG: Stamp current task 1 (/home/chunyun/yocto/hello/meta-test/recipes-example/firstrecipe/firstrecipe_0.0.bb, do_unpack)  
DEBUG: Marking task 2 (/home/chunyun/yocto/hello/meta-test/recipes-example/firstrecipe/firstrecipe_0.0.bb, do_patch) as buildable  
DEBUG: Stamp current task 2 (/home/chunyun/yocto/hello/meta-test/recipes-example/firstrecipe/firstrecipe_0.0.bb, do_patch)  
DEBUG: Marking task 3 (/home/chunyun/yocto/hello/meta-test/recipes-example/firstrecipe/firstrecipe_0.0.bb, do_configure) as buildable  
DEBUG: Stamp current task 3 (/home/chunyun/yocto/hello/meta-test/recipes-example/firstrecipe/firstrecipe_0.0.bb, do_configure)  
DEBUG: Marking task 4 (/home/chunyun/yocto/hello/meta-test/recipes-example/firstrecipe/firstrecipe_0.0.bb, do_make) as buildable  
DEBUG: Stamp current task 4 (/home/chunyun/yocto/hello/meta-test/recipes-example/firstrecipe/firstrecipe_0.0.bb, do_make)  
DEBUG: Marking task 5 (/home/chunyun/yocto/hello/meta-test/recipes-example/firstrecipe/firstrecipe_0.0.bb, do_install) as buildable  
DEBUG: Stamp current task 5 (/home/chunyun/yocto/hello/meta-test/recipes-example/firstrecipe/firstrecipe_0.0.bb, do_install)  
DEBUG: Marking task 6 (/home/chunyun/yocto/hello/meta-test/recipes-example/firstrecipe/firstrecipe_0.0.bb, do_build) as buildable  
DEBUG: Stamp current task 6 (/home/chunyun/yocto/hello/meta-test/recipes-example/firstrecipe/firstrecipe_0.0.bb, do_build)  
DEBUG: Teardown for bitbake-worker  
DEBUG: Found bblayers.conf (/home/chunyun/yocto/hello/conf/bblayers.conf)  
DEBUG: Adding layer /home/chunyun/yocto/hello/meta-test  
DEBUG: Inheriting /home/chunyun/yocto/hello/classes/base.bbclass (from configuration INHERITs:0)  
DEBUG: Inheriting /home/chunyun/yocto/hello/classes/logging.bbclass (from /home/chunyun/yocto/hello/classes/base.bbclass:3)  
DEBUG: Using cache in '/home/chunyun/yocto/hello/tmp/cache/bb_codeparser.dat'  
NOTE: Tasks Summary: Attempted 7 tasks of which 7 didn't need to be rerun and all succeeded. 
