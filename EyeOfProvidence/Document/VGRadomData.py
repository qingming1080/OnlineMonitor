import socket
import time
import random

# 服务器配置
HOST = '192.168.1.88'
PORT = 4200

# 初始模板数据
data_template = "10145\t1/1/2003\t12:10:47 AM\tAmtech SU\t\t25\t25.00\t25.0\t15\t\t5.00\t0.00\t4800\t0\t15.00\t0.00\t15.00\t0.00\t\t0.05\t1143\t0.26\t0.24\t-\t1ms"

# 创建 TCP socket
server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server.bind((HOST, PORT))
server.listen(1)
print(f"服务器启动，等待客户端连接 {HOST}:{PORT} ...")

conn, addr = server.accept()
print(f"客户端已连接：{addr}")

counter = 1

try:
    while True:
        # 拆分模板成列
        columns = data_template.split('\t')

        # 修改 ID 列
        columns[0] = str(counter)

        # 修改特定列
        columns[19] = f"{round(random.uniform(0.05, 0.06), 3)}"  # 列20 焊接时间
        columns[20] = str(random.randint(1200, 1500))              # 列21 峰值功率
        columns[21] = f"{round(random.uniform(14.8, 15.0), 2)}"  # 列22 焊前高度
        columns[22] = f"{round(random.uniform(14.8, 15.0), 2)}"  # 列23 焊后高度

        # 重新拼接成数据帧
        data_to_send = '\t'.join(columns)

        conn.sendall(data_to_send.encode('utf-8'))
        print(f"已发送: {data_to_send}")
        counter += 1
        time.sleep(1)

except KeyboardInterrupt:
    print("服务器关闭")
finally:
    conn.close()
    server.close()
