
> This is a small http server project.  完善中......




前提：需要在 sql.cpp 中修改自己的数据库表 以及连接数据库的信息

使用方法:

```
mkidr http

cd http

git clone https://github.com/HuoZhiGang/HTTP_SERVER.git

git cd HTTP_SERVER/

./build.sh

cd output/
# 启动服务
./ctl_server.sh -s

# 关闭
./ctl_server.sh -t

# 状态
./ctl_server.sh -ss
```
