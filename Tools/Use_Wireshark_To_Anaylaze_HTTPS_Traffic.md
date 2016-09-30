#使Wireshark能够分析HTTPS的流量
主要有两种方式
##获取网站证书解析
太麻烦了不写了QAQ
主要是效果也不如设置环境变量，因为获取网站私钥并不是一个容易的事情


##设置环境变量
设置环境变量 SSLKEYLOGFILE，将其指向一个可写入的文本文件。Chrome和Firefox在启动时会检查这个环境变量，如果存在的话，它会向指定的文件写入访问HTTPS站点时使用的密钥。我们可以在客户端配置Wireshark读取这个文件来解码TLS、 SSL网络包。
- 右键计算机，查看属性，打开高级系统设置，查看高级选项卡，点击环境变量。
- 新建一个系统变量。
- 指定变量名为：SSLKEYLOGFILE，变量值为一个可写入的文本文件。文件夹必须提前创建，若文件尚未创建，可以打开Chrome或Firefox一下，文件会被自动创建。
- 在Wireshark中，进入菜单 Edit -> Preferences..
- 展开 Protocols -> SSL，将 (Pre)-Master-Secret log filename 设为步骤3中指定的值。
- 点击确认后，就会正确解码HTTPS网络包了。使用 SSLKEYLOGFILE 的好处就是它可以解Diffie-Hellman加密算法。

