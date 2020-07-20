    # 基于xinetd的简易web服务器
    make

    1.在这之前，你的安装好xinetd，
    如一安装好请忽略此步骤
    sudo apt-get install xinetd
    2.配置xinetd服务器
    cp ./config/xhttpd /etc/xinetd.d/
    vi /etc/xinetd.d/xhttpd
    service xhttpd（xxxx）
    {
        socket_type = stream
        protocol    = tcp
        wait        = no
        user        = qyz（你的用户名称）
        server      = /home/qyz/Desktop/linux/web/xhttpd（xxxx）                        
        server_args = /home/qyz/dir （需要访问的目录）
        disable     = no
        flags       = IPv4
    }
    注意：该文件中不要使用空格，最好使用缩进，不然有可能会出现问题
    其中xxxx表示服务名称，可以修改，但是需要同步，例如改为myxhttpd
    则该文件名也需要把xhttpd 改为 myxhttpd
    3.添加端口 文件末尾添加
    vi /etc/server
    xhttpd 9988/tcp  #xhttpd server 
    xhttpd 9988/udp
    注意： 如果之前修改了服务名称如 myxhttpd ，请做相应的修改 
    4.重启xinetd服务
    sudo service xinetd restart

    如需删除.o文件
    make claer_o
    如需删除可执行文件
    make clear_target
