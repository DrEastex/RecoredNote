老猫是 HG8240F 
  
用 华为 ONT 工具恢复 telnet 功能，进去之后 
  
display lanmac 
display sn 
display boardItem 
display machineItem 
  
然后登录 web，把 voip 的设置记录一下，当然也可以 telnet 进去之后，用  
aesdecrypt2 解密 xml 获得，还有一个是最后一个 tab 有调试工具，可以下载一个完整 
的 debug 信息，里面包含了所有需要的信息。 
  
新猫淘宝买的，需要地址 dm 吧，似乎发不出来。 
拿到猫之后，直接 telnet 进去 
  
set lanmac MAC xxx 
set sn snid xxx 
set boardItem ItemId xxx 
set machineItem ItemId xxx 
  
xxx 就是上面备份的信息啦 
  
然后再登录 web 进行 voip 的设置，不需要电话直接跳过好了 
  
设置好之后，把旧猫拔掉直接换成新猫，自动拨号，妥了。 


要用TELNET命令改
SU下

修改 LAN MAC. 
set lanmac MAC 00:00:00:00:00:0A
修改 WAN MAC
set wan MAC 00:00:00:00:00:0B
修改 无线 MAC
set wlanmac MAC 00:00:00:00:00:0C

修改 PON SN (PON No)
set sn snid 1234567890123456 (16位)
修改 整机条码 (PROD ID)
set machineItem ItemId 12345678901234567890 (20位)


在 SU 下执行：

设置电信工单上电信的Loid号
set password eponkey xxxxxxxxxxxxxx

修改 LAN MAC
set lanmac MAC 00:00:00:00:00:0A

修改 WAN MAC
set wan MAC 00:00:00:00:00:0B

修改 无线 MAC
set wlanmac MAC 00:00:00:00:00:0C

修改 PON SN (PON No)
set sn snid 1234567890123456 (16位)
