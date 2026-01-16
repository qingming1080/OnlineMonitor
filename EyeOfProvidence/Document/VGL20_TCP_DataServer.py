import socket
import time

# 服务器配置
HOST = '192.168.1.55'  # 本地测试，可以改成服务器IP
PORT = 4200         # 端口号

# 初始数据
data_template = "10145\t1/1/2003\t12:10:47 AM\tAmtech SU\t\t25\t25.00\t25.0\t15\t\t5.00\t0.00\t4800\t0\t15.00\t0.00\t15.00\t0.00\t\t0.05\t1143\t0.26\t0.24\t-\t1ms"

# 创建 TCP socket
server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server.bind((HOST, PORT))
server.listen(1)
print(f"服务器启动，等待客户端连接 {HOST}:{PORT} ...")

conn, addr = server.accept()
print(f"客户端已连接：{addr}")

counter = 1  # 初始值

try:
    while True:
        # 构造数据，每次发送第一个字段递增
        data_to_send = f"{counter}" + data_template[data_template.find('\t'):]
        conn.sendall(data_to_send.encode('utf-8'))
        print(f"已发送: {data_to_send}")
        counter += 1
        time.sleep(1)  # 每秒发送一次，可修改间隔
except KeyboardInterrupt:
    print("服务器关闭")
finally:
    conn.close()
    server.close()
