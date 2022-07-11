//输入输出代码演示
#include<stdio.h>
int main(){
    int n;
    char str[100] = {0};
    int arr[4] = {0};
    // scanf("%d", &n); //stdin 标准输入
    // printf("%d\n", n); //stdout 标准输入  
    // 都是返回元素个数
    sprintf(str, "%d.%d.%d.%d", 192,168,0,1);
    printf("str = %s\n", str);
    sscanf(str, "%d.%d.%d.%d",&arr[0],&arr[1],&arr[2],&arr[3]);
    for(int i=0;i<4;i++){
        printf("%d\n",arr[i]);
    }
    FILE *fp=fopen("./output","a+");
    fprintf(fp,"str = %s\n",str);
    fclose(fp);
    char ans[100] = {0}, temp;
    int offset = 0;
    FILE *fin = fopen("./output", "r");
    while (fscanf(fin, "%c", &temp) != EOF) {
        offset += sprintf(ans + offset, "%c", temp);
    }
    fclose(fin);
    printf("%s", ans);
    return 0;
}