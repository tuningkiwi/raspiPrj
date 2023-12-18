#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(int argc, char** argv){

	int n, in, out;
	char buf[1024];

	if(argc<3){
		write(2, "Usage:copy file1 file2 \n",25);
		return -1;
	}

	/*복사의 원본이 되는 파일을 읽기 모드로 연다 */
	if((in= open(argv[1],O_RDONLY)) <0){
		perror(argv[1]);
		return -1;
	}

	/*복사할 결과 파일을 쓰기 모드 (새로운 파일 생성 | 기존에 파일 내용 지움)로 연다*/
	if((out = open(argv[2],O_WRONLY|O_CREAT|O_TRUNC, S_IRUSR|S_IWUSR))<0){
		perror(argv[2]);
		return -1;
	}

	/*원본 파일의 내용을 읽어서 복사할 파일에 쓴다 */
	while((n=read(in, buf, sizeof(buf)))>0){
		write(out, buf, n);
	}

	/*열린 파일들을 닫는다*/
	close(out);
	close(in);

	return 0;
}
