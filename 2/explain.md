```c
// DOWHILE 函式處理 do-while 迴圈的解析
void DOWHILE() {
  // 宣告迴圈開始和結束的標籤
  int whileBegin = nextLabel();
  int whileEnd = nextLabel();

  // 跳過關鍵字 "do"
  skip("do");

  // 產生迴圈開始的標籤
  emit("(L%d)\n", whileBegin);

  // 處理迴圈內的陳述
  STMT();

  // 跳過關鍵字 "while"
  skip("while");

  // 跳過左括號 "("
  skip("(");

  // 處理迴圈的條件表達式，並將結果存儲在變數 e 中
  int e = E();

  // 產生條件判斷的程式碼，若條件不滿足則跳轉到迴圈開始標籤
  emit("if T%d goto L%d\n", e, whileBegin);

  // 跳過右括號 ")"
  skip(")");

  // 跳過分號 ";"
  skip(";");
}

void STMT() {
  if(isNext("do"))
    return DOWHILE();
    .
    .
    .
```