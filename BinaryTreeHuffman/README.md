二叉树和Huffman编码
====
实现功能
----
设二叉树以二叉链表的形式保存，T为指向根结点的指针。试完成以下功能：<br>
1、建立二叉树：从键盘输入各结点的值，可参照二叉树的顺序存储方式。例如输入“a,b,c,&nbsp;,d”表示结点a是根，b和c是a的两个孩子，b仅有右孩子d。<br>
2、统计T中叶结点的个数。<br>
3、统计T中度为2的结点的个数。<br>
4、求树T的高度。<br>
5、判断T中是否有度为1的结点（即按照国外教材的定义，是否为满树）。<br>

在此基础上，实现Huffman编码及译码，达到以下两个目标：<br>
1、掌握二叉树的二叉链表存贮结构。<br>
2、掌握Huffman算法。<br>

## 要求：
#### 使用文件保存初始的文本数据及最终的结果。<br>
1.文件名为inputfile1.txt的文件保存的是一段英文短文；<br>
2.文件名为inputfile2.txt的文件保存01形式的编码段；<br>
3.文件名为outputfile1.txt的文件保存各字符的出现次数和对应的编码；<br>
4.文件名为outputfile2.txt的文件保存对应于inputfile2.txt的译码结果。<br>

#### 统计inputfile1.txt中各字符的出现频率，并据此构造Huffman树，编制Huffman编码；根据已经得到的编码，对01形式的编码段进行译码。<br>
##### 具体的要求：<br>
1.将给定字符文件编码：生成编码，输出每个字符出现的次数和编码；<br>
2.将给定编码文件译码：生成字符，输出编码及其对应字符。<br>

##### 输入数据格式：
详见要求部分。<br>

###### 输出数据格式:
outputfile1.txt文件中：<br>
|字符|出现次数|对应的编码|
|----|----|----|
|a|37|010|
|b|130|00|

outputfile2.txt文件中：<br>
This is a example.<br>


