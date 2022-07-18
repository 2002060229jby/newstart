## docker容器相较于虚拟机的优势

|            | docker容器              | 虚拟机(VM)                  |
| ---------- | ----------------------- | --------------------------- |
| 操作系统： | 与宿主机共享OS          | 宿主机OS上运行虚拟机OS      |
| 存储大小   | 镜像小，便于存储于传输  | 镜像庞大(vmdk/vdi)          |
| 运行性能   | 几乎无额外性能损失      | 操作系统额外的CPU、内存泄漏 |
| 移植性     | 轻便、灵活、适应于linux | 笨重，与虚拟化技术耦合度高  |
| 硬件亲和性 | 面向软件开发者          | 面向硬件运维者              |
| 部署速度   | 快速，秒速              | 较慢，10s以上               |

docker run -d -p 5000:5000 -v /jbyuse/myregistry/:/tmp/registry --privileged=true registry



docker commit -m="ifconfig cmd add" -a="jby" a832a105e27c jbyubuntu:1.2



curl -XGET http://192.168.109.139:5000/v2/_catalog



docker tag jbyubuntu:1.2 192.168.109.139:5000/jbyubuntu:1.2



### 数据卷

docker run -it --privileged=true -v /tmp/host_data:/tmp/docker_data --name=u1 ubuntu

docker run -it --privileged=true -v /mydocker/u:/tmp/u:ro --name u2 ubuntu



docker run -it --privileged=true --volumes-from u1 --name u2 ubuntu
