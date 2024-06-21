## 使用說明

1. 編譯 server 程式
在終端機中，使用以下命令編譯 server 程式：

bash
複製程式碼
gcc -o server server.c -pthread
這條命令會將 server.c 檔案編譯為可執行檔 server，並鏈接 pthread 函式庫。

2. 運行 server 程式
編譯完成後，運行 server 程式：

bash
複製程式碼
./server
運行後，server 會在指定的端口（此例中為 8080）上啟動，並準備接受 client 連接。server 會顯示一個提示符 server>，允許你輸入指令。

3. 編譯 client 程式
在另一個終端機中，使用以下命令編譯 client 程式：

bash
複製程式碼
gcc -o client client.c -pthread
這條命令會將 client.c 檔案編譯為可執行檔 client，並鏈接 pthread 函式庫。

4. 運行 client 程式
編譯完成後，運行 client 程式：

bash
複製程式碼
./client
運行後，client 會連接到 server。如果連接成功，終端機會顯示 "Connected to server"。

5. 在 server 上執行指令
在 server 的終端機上，你可以輸入任何有效的 shell 指令，例如 ls、date、uptime 等，並按下 Enter 鍵來執行。指令的結果會顯示在 server 終端機上，並且會廣播給所有已連接的 client。

例如：

plaintext
複製程式碼
server> ls
會在 server 終端機上顯示目錄內容，同時所有 client 也會收到並顯示這些內容。

6. 多個 client 連接
你可以在不同的終端機或不同的機器上運行多個 client 程式。每個 client 連接成功後都能接收到 server 上的所有指令輸入和執行結果。

7. 停止 server 和 client
要停止 server 程式，可以在 server 終端機中按下 Ctrl+C。這將中斷 server 的運行。

要停止 client 程式，可以在 client 終端機中按下 Ctrl+C。這將中斷 client 的運行。