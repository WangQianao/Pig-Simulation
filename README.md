# Pig-Simulation
小明开了个养猪场，一共有100个猪圈（按照0-99编号），每个猪圈最多养10头猪（按照0到9编号），猪一共有三个品种：黑猪、小花猪和大花白猪，其中黑猪不能与其他两种猪放在一个猪圈里，会打架。规定每3个月，养猪场要出圈一批猪，包括：体重超过150斤的和饲养超过1年的；同时补充一批猪崽儿（猪的品种、数量录入或者选择随机生成），每一头黑猪猪崽910元，小花猪350元一头，大花白猪280元一头。试利用随机数方法构造猪崽儿的初始体重等信息（20-50kg），利用随机数方法按照秒或次数刷新每头猪随时间的体重增长函数（一秒/一次表示一天，一天增重0.0 ~1.2kg）。试利用结构体链表形式管理猪圈的猪，为新进的猪自动分配猪圈（要求猪均匀分布在各个猪圈中），自动统计本次出圈的猪的总体售价（黑猪15元一斤，小花猪7元一斤，大花白猪6元一斤）；
（1）可任意查询当前某一猪圈的猪的数量和种类； 
（2）可任意查询当前某一猪圈某头猪的状态信息； 
（3）可任意统计猪场每个品种猪的数量当前和体重、饲养时间分布情况；
（4）可任意查询近5年猪的销售记录和猪崽儿的购入记录（记录用文件形式存储）；
 （5）所有当前猪的信息使用文件形式保存，程序再启动时，自动读取养猪场信息并显示。
 （6）模拟养猪场某一只猪得了猪瘟，猪瘟的扩展几率是，同一个猪圈的猪每天被传染几率是50%，相邻猪圈的猪每天被传染的几率是15%，不相邻的猪圈的猪不传染。编写程序模拟多久后养猪场的猪死光光。 
（7）当发现有猪得了猪瘟已经发病后，请采取合理的隔离措施，进行风险控制。 
提高部分：（1）可使用MFC 或者QT等IDE设计用户界面；（2）显示每个品种猪的数量和体重、饲养时间分布图；（3）可根据自己的理解，加入功能（比如转换为一个养猪游戏）。
