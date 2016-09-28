Bitbake介绍
oe bitbake一种软件组建自动化工具程式，像所有的build工具一样(比如make，ant，jam)控制如何去构建系统并且解决构建依赖。但是又区别于功能单一的工程管理工具(比如make)，bitbake不是基于把依赖写死了的makefile，而是收集和管理大量之间没有依赖关系的描述文件(这里我们称为包的配方)，然后自动按照正确的顺序进行构建。oe代表OpenEmbedded，而openembedded是一些用来交叉编译，安装和打包的metadata(元数据)。
OpenEmbedded是一些脚本（shell和python脚本）和数据构成的自动构建系统。
    脚本实现构建过程，包括下载（fetch）、解包（unpack）、打补丁（patch）、configure、编译（compile）、安装（install）、打包（package）、staging、做安装包（package_write_ipk）、构建文件系统等。
    数据主要提供两个方面的信息：
    特定软件包的构建信息。怎样获取源代码和补丁？怎样构建，用Makefile还是Autotool？需要向目标编译环境输出哪些文件？需要安装哪些文件？每个软件包都需要描述文件。事实上，每个软件包的不同版本都有一个描述文件。
     软件包之间的依赖关系。构建软件包A需要先构建什么主机平台工具，什么目标平台工具？软件包A在编译时依赖哪些软件包？软件包A在运行时依赖哪些软件包？一个目标应包含那些软件包，这些依赖关系把几百个软件包联系在一起，构成了一个完整的系统。 

基于bitbake，OE可以满足以下所有要求： 
 ※ 解决交叉编译
 ※ 解决包之间的依赖关系
 ※ 必须支持包的管理（tar,rpm,ipk）
 ※ 必须支持将包作成镜像
 ※ 必须支持高度的可定制性，以满足不同的机器，主机发行版和架构需求
 ※ 编写元数据必须是容易的，并且可重用性要好

bitbake的使用方法
1 获取*.bb文件中包的依赖关系的命令格式
bitbake linux-qr-eagle8074 –g
执行后，最终生成下列四个文件，用于描述recipes的依赖关系，使用文本编辑器查看文件。
package-depends.dot: Shows BitBake's knowledge of dependencies between runtime targets.
pn-depends.dot: Shows dependencies between build-time targets (i.e. recipes).
task-depends.dot: Shows dependencies between tasks.
pn-buildlist: Shows a simple list of targets that are to be built.
或者安装graphviz软件实现依赖关系文件的转化，比如转换命令：
fdp -Tsvg package-depends.dot -o package-depends.svg
得到svg图像之后，使用firefox或图像查看器打开，直观的查看运行时、编译时包的依赖关系、以及Task之间的依赖关系，但是由于当前bitbake的依赖关系很复杂，会导致输出的图像不容易查看，需要一点点的分析，最终找到各个依赖关系。

2 文件系统里的OpenEmbedded
    OE环境中最重要的目录有3个：放工具的bitbake目录、放元数据的目录、和执行构建的build目录。
    bitbake目录
    这个目录里是我们的烹饪工具：bitbake。我们使用它，但通常不需要访问它
    元数据目录
    在poky中元数据目录是meta。Openmoko中元数据目录是openembedded。在元数据目录中，有3个目录里是真正的元数据。它们是：classes、conf和packages。
    packages目录
    所有的配方(recipes)文件（以.bb为后缀名）都放在package目录。每个相对独立的软件包或构建任务在package目录下都有自己的子目录。在一个子目录中可以有多个配方(recipes)文件。它们可能是同一个软件包的不同版本。也可能描述了基于同一个软件包的不同构建目标。
    有的配方(recipes)简单,有的配方(recipes)复杂。简单的配方(recipes)仅描述一个软件包的构建。最复杂的配方(recipes)就是要求构建文件系统的配方(recipes)，这个配方(recipes)文件本身并不长，甚至还很短，但它通过依赖关系将几百个甚至几千个其它配方(recipes)件卷入了构建过程。 packages目录的images子目录下就是这些要求构建文件系统的配方(recipes)。
    classes目录
    这个目录放的是配方(recipes)的类文件（以.bbclass为后缀名）。类文件包含了一些bitbake任务的定义，例如怎么配置、怎么安装。配方(recipes)文件继承类文件，就继承了这些任务的定义。例如：我们如果增加一个使用autotool的软件包，只要在配方(recipes)文件中继承autotools.bbclass：
    inherit autotools
    bitbake就知道怎样使用autotool工具配置、编译、安装了。所有的配方(recipes)文件都自动继承了base.bbclass。 base.bbclass提供了大部分bitbake任务的默认实现。
    一个配方(recipes)文件可以继承多个类文件。以后的文章会介绍bitbake的任务，届时会更详细地讨论bitbake的继承。目前，我们只要知道继承类文件是一种构建过程的复用方式就可以了。
    conf目录
    conf目录包含编译系统的配置文件（以.conf为后缀名）。bitbake在启动时会执行bitbake.conf。
    bitbake.conf会装载用户提供的local.conf。然后根据用户在local.conf中定义的硬件平台（MACHINE）和发布目标（DISTRO）装载machine子目录和distro子目录的配置文件。machine子目录里是硬件平台相关的配置文件。distro子目录里是与发布目标相关的配置文件。配置文件负责设置bitbake内部使用的环境变量。这些变量会影响整个构建过程。
    build目录
    build是我们烹饪嵌入式系统的大厨房。整个构建过程就是在build目录的tmp子目录完成的。 build目录的conf子目录里是用户的配置文件local.conf。
    tmp目录有7个子目录：cache、cross、rootfs、staging、work、deploy和stamps目录。其中cache是bitbake内部使用的缓存目录。cross是构建过程中产生的交互编译器。所谓交互编译器就是在主机平台运行，用于编译目标平台代码的编译器。  rootfs是制作文件系统映像前临时建立的根文件系统。我们在工作中通常不需要访问这3个目录。我们访问比较多的是其它4个目录：staging、work、deploy和stamps目录。
    1. staging目录
    软件包B在构建时可能依赖软件包A提供的头文件、库文件，也可能要使用软件包C生成的工具。 staging目录就是放这些输出文件的地方。
    我们必须在配方(recipes)文件中用“DEPENDS”变量声明构建时的依赖关系。bitbake就会在构建软件包B前先构建软件包A和软件包C，并将软件包B需要的头文件、库文件、和工具放在staging目录。这样，在构建软件包， 时就可以从staging目录得到需要的头文件、库文件、和工具。
    2. work目录
    所有软件包的解包、打补丁、配置、编译、安装等工作都是在work目录进行的。所以work目录包含了整个嵌入式系统的完整源代码。
    work目录下按照硬件平台、发行人、目标平台的不同又分了几个子目录。所有软件包都被放在对应子目录中。每个软件包都有一个独立的目录。因为软件包总是 根据一个配方(recipes)文件构建的，所以软件包所在的目录就是对应配方(recipes)文件的工作目录。在讨论bitbake和配方(recipes)文件时我们还会回来，更仔细地观察配方(recipes)文件的工作
    3 deploy目录
    这是保存输出成果的目录。其中images目录保存构建成功后产生的文件系统映像、内核映像。 ipk目录保存每个软件包的安装包。我们在修改、构建软件包后，可以在目标平台手工安装ipk目录下的对应安装包。确认没有问题后，再制作文件系统映像。
    4 stamps目录
    和work目录类似，stamps目录也按照硬件平台、发行人、目标平台的不同又分了几个子目录。软件包在完成每个bitbake任务后都会在对应子目录里touch一个对应任务的时间戳。有时我们会手工删除某个软件包的时间戳，强制bitbake重新构建这个软件包。
    sources目录
    OE环境的sources目录是一个储藏间，用来放从网上下载的源代码包。 fetch任务负责下载代码，放到sources目录。

bitbake的配方文件编写
二进制文件安装到目标目录的recipes配方
SUMMARY = " Source Code Compile" 
DESCRIPTION = "Test " 
HOMEPAGE = "" 

LICENSE = "Commercial" 
LIC_FILES_CHKSUM = "file://${COREBASE}/meta/COPYING.MIT;md5=3da9cfbcb788c80a0384361b4de20420" 

PR = "r0" 

PACKAGES = "${PN}" 
PACKAGES += " ${PN}-dbg" 
FILES_${PN} = "\ 
    /usr/lib/* \ 
    /usr/include/*" 

FILES_${PN}-dbg = "/usr/lib/.debug/*" 

do_configure(){ 
   cp -lr "${TOPDIR}"/../hello-mod/files/* ${S}/ 
} 

do_install(){ 
    export STRIP="" 
    install -d ${D}${includedir} 
    install -m 0755 ${S}/CL/* ${D}${includedir} 

    install -d ${D}${libdir} 
    install -m 0755 ${S}/lib/* ${D}${libdir} 
}

源码文件编译得到二进制文件，并安装到目标目录的recipes配方
SUMMARY = " Source Code Compile" DESCRIPTION = "Test " HOMEPAGE = "" LICENSE = "Commercial" LIC_FILES_CHKSUM = "file://${COREBASE}/meta/COPYING.MIT;md5=3da9cfbcb788c80a0384361b4de20420" PV = "1.0" PR = "r0" DEPENDS += "aaaaa" CFLAGS += "-isystem${STAGING_INCDIR}/linux-headers/usr/include" CXXFLAGS += "-isystem${STAGING_INCDIR}/linux-headers/usr/include" PACKAGES = "${PN}" FILES_${PN} = "\     /usr/bin/hello-world" PACKAGES += " ${PN}-dbg" FILES_${PN}-dbg = "\           /usr/bin/.debug/* \                   /usr/src/debug/* " PACKAGES += " ${PN}-lib" FILES_${PN}-lib = "/usr/lib/* \" do_configure(){    cp -lr ${TOPDIR}/../hello-world/files/* ${S}/ } do_compile (){    export ARCH="arm"    make } do_install(){     install -d ${D}${bindir}     install -m 0755 ${S}/hello-world ${D}${bindir}     install -d ${D}${libdir}     install -m 0755 ${S}/lib/* ${D}${libdir} }
