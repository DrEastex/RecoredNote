# LAMP配置以及，所有的坑
## 安装sshd
首先安装sshd以保证能够远程连接
```
sudo apt-get install openssh-server
```
配置后启动

## 安装及配置samba
安装samba及相关服务
```
sudo apt-get install samba
```

添加samba用户

```
sudo smbpasswd -a eastex
```

编辑samba配置文件
```
sudo vi /etc/samba/smb.conf
```
在文件最后添加
```
[Shares]
   path = /home/shengxiao
   writeable = yes
   guest ok = no
   write list = shengxiao
```

其中 
 ```path ```替换要共享的路径

## 安装zlib
```
sudo apt-get install zlib1g-dev
```

## 安装libxml2
```
sudo apt-get install libxml2-dev
```

## 安装gcc g++以及make
```
sudo apt-get install gcc g++ make
```

## 下载并安装配置OpenSSL
```
sudo wget https://www.openssl.org/source/openssl-1.0.1t.tar.gz
sudo tar -zxvf openssl-1.0.1t.tar.gz
cd openssl-1.0.1t
sudo ./config shared --prefix=/usr/local/openssl
sudo make
sudo make install
```

## 下载并安装配置apr
```
sudo wget http://mirrors.hust.edu.cn/apache/apr/apr-1.5.2.tar.gz
sudo tar -zxvf apr-1.5.2.tar.gz
cd apr-1.5.2
sudo ./configure --prefix=/usr/local/apr
sudo make
sudo make install
```

## 下载并安装配置apr-utils
```
sudo wget http://mirrors.hust.edu.cn/apache/apr/apr-util-1.5.4.tar.gz
sudo tar -zxvf apr-util-1.5.4.tar.gz
cd apr-util-1.5.4
sudo ./configure --prefix=/usr/local/apr-util --with-apr=/usr/local/apr/bin/apr-1-config
sudo make
sudo make install
```

## 下载并安装配置pcre
```
sudo wget http://tcpdiag.dl.sourceforge.net/project/pcre/pcre/8.36/pcre-8.36.tar.bz2
sudo tar -zxvf pcre-8.36.tar.bz2
cd pcre-8.36
sudo ./configure --prefix=/usr/local/pcre --with-apr=/usr/local/apr/bin/apr-1-config
sudo make
sudo make install
```

## 下载并安装apache2
```
sudo wget http://mirror.bit.edu.cn/apache//httpd/httpd-2.4.20.tar.gz
sudo tar -zxvf httpd-2.4.20.tar.gz
cd httpd-2.4.20
sudo ./configure --with-apr=/usr/local/apr --with-apr-util=/usr/local/apr-util --with-pcre=/usr/local/pcre --enable-ssl --enable-so  --prefix=/usr/local/apache2 --enable-rewrite --enable-ssl --with-ssl=/usr/local/openssl 
sudo make
sudo make install
```

## 安装MySQL
```
sudo apt-get install mysql-server
```

## 下载并安装PHP
```
sudo wget newest php.code
http://cn2.php.net/distributions/php-5.6.22.tar.gz
./configure --prefix=/usr/local/php --with-config-file-path=/usr/local/php/etc --enable-fpm --enable-sysvsem --enable-sockets --enable-pcntl --enable-mbstring --enable-mysqlnd --enable-opcache --enable-shmop --enable-zip --enable-ftp --enable-gd-native-ttf --enable-wddx --enable-soap --with-apxs2=/usr/local/apache2/bin/apxs --with-openssl   --with-mysql --enable-cli 
```

## 配置apache支持PHP
- 添加index.php
- 
```
 AddType application/x-httpd-php .php .php3 .phtml .inc
AddType application/x-httpd-php-source .phps
```
## Https相关设置

- 修改
```httpd.conf```配置
 
  开启http重定向
``` LoadModule rewrite_module modules/mod_rewrite.so ```

```
<Directory />
    AllowOverride ALL
    Require all denied
</Directory>

DocumentRoot "/usr/local/apache2/htdocs"
<Directory "/usr/local/apache2/htdocs">
    #
    # Possible values for the Options directive are "None", "All",
    # or any combination of:
    #   Indexes Includes FollowSymLinks SymLinksifOwnerMatch ExecCGI MultiViews
    #
    # Note that "MultiViews" must be named *explicitly* --- "Options All"
    # doesn't give it to you.
    #
    # The Options directive is both complicated and important.  Please see
    # http://httpd.apache.org/docs/2.4/mod/core.html#options
    # for more information.
    #
    Options Indexes FollowSymLinks

    #
    # AllowOverride controls what directives may be placed in .htaccess files.
    # It can be "All", "None", or any combination of the keywords:
    #   AllowOverride FileInfo AuthConfig Limit
    #
    AllowOverride ALL

    #
    # Controls who can get stuff from this server.
    #
    Require all granted
</Directory>
```
- 在网站根目录添加```.htaccess```文件
内容如下

```
RewriteEngine on
RewriteCond %{SERVER_PORT} !^443$
RewriteCond %{REQUEST_URI} !^/tz.php
RewriteRule (.*) https://%{SERVER_NAME}/$1 [R]
```

- Listen 443Port
- 启用mod_ssl
- 启用mod_socache_shmcb.so
- 启用Include conf/extra/httpd-ssl.conf
- 配置conf/extra/httpd-ssl.conf 证书以及根目录等信息

如果修改了apache根路径
可能涉及两处改动
```httpd.conf```和```extra/mod_ssl.conf ```

## 修改MySQL数据库保存位置
更改MySQL数据库存放位置：
- 停用MySQL服务   /etc/init.d/mysql stop
- 把默认的/var/lib/mysql转移到目标位置
- /etc/mysql/my.cnf相关的配置文件修改 datadir这一行
- 修改/etc/apparmor.d/usr.sbin.mysqld   将/var/lib/mysql相关的配置项重新设定为改后的位置
- /etc/init.d/apparmor reload 来重置apparmor服务
- 修改新的MySQL路径权限为mysql:mysql
- 启动MySQL服务  /etc/init.d/mysql start







