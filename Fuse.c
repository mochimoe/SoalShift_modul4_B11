#define FUSE_USE_VERSION 28
#include <fuse.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <errno.h>
#include <sys/time.h>
#include <grp.h>
#include <pwd.h>
#include <time.h>

const char* owner1 = "chipset";
const char* owner2 = "ic_controller";
const char* group = "rusak";
const char charlist[1000]="qE1~ YMUR2\"`hNIdPzi%^t@(Ao:=CQ,nx4S[7mHFye#aT6+v)DfKL$r?bkOGB>}!9_wV']jcp5JZ&Xl|\\8s;g<{3.u*W-0";

static const char *dirpath = "/home/iotatfan/shift4/AFSHiaAP";

static int xmp_getattr(const char *path, struct stat *stbuf)
{
	// const char charlist[1000]="qE1~ YMUR2\"`hNIdPzi%^t@(Ao:=CQ,nx4S[7mHFye#aT6+v)DfKL$r?bkOGB>}!9_wV']jcp5JZ&Xl|\\8s;g<{3.u*W-0";
	int key = 17;
	char ch;
	int i,j,res;

	char final[1000];
	char fpath[1000];
	char encode[strlen(path)];
	strcpy(encode,path);

	for(i=0;i<strlen(encode);i++) {
		ch=encode[i];
		if(ch=='/') {
			encode[i]=ch;
		}
		else {
			j=0;
			while(ch!=charlist[j]) {
				j++;
			}
			j=(j+key)%strlen(charlist);
			encode[i]=charlist[j];
		}
	}
	puts(encode);
	
	strcpy(fpath,encode);
	sprintf(final,"%s%s",dirpath,fpath);

	res = lstat(final, stbuf);

	if (res == -1)
		return -errno;

	return 0;
}

static int xmp_mkdir(const char *path, mode_t mode)
{
	char final[1000];
	int i,j;
	char ch;

	if(strstr(path,"YOUTUBER")) {
		mode=0750;
	}

	if(strcmp(path,"/") == 0)
	{
		path=dirpath;
		sprintf(final,"%s",path);
	}
	else {
		char encode[strlen(path)];
		strcpy(encode,path);
		for(i=0;i<strlen(encode);i++) {
			ch=encode[i];
			if(ch=='/') {
				encode[i]=ch;
			}
			else {
				j=0;
				while(ch!=charlist[j]) {
					j++;
				}
				j=(j+17)%strlen(charlist);
				encode[i]=charlist[j];
			}
		}
		sprintf(final,"%s%s",dirpath,encode);
	}
    int res;

    res = mkdir(final, mode);
    if(res == -1)
        return -errno;

    return 0;
}

static int xmp_chmod(const char *path, mode_t mode)
{
    int res;

	char final[1000];
	int i,j;
	char ch;

	if(strstr(path,".iz1")) {
		pid_t child_id;
		child_id=fork();

		if(child_id==0) {
			char* argv[] = {"zenity","--error","--text=File ekstensi iz1 tidak boleh diubah permissionnya.\n",NULL};
			execv("/usr/bin/zenity",argv);
		}

		return 0;
	}

	if(strcmp(path,"/") == 0)
	{
		path=dirpath;
		sprintf(final,"%s",path);
	}
	else {
		char encode[strlen(path)];
		strcpy(encode,path);
		for(i=0;i<strlen(encode);i++) {
			ch=encode[i];
			if(ch=='/') {
				encode[i]=ch;
			}
			else {
				j=0;
				while(ch!=charlist[j]) {
					j++;
				}
				j=(j+17)%strlen(charlist);
				encode[i]=charlist[j];
			}
		}
		sprintf(final,"%s%s",dirpath,encode);
	}

    res = chmod(final, mode);
    if(res == -1)
        return -errno;
    
    return 0;
}

static int xmp_readdir(const char *path, void *buf, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info *fi)
{
	char final[1000];
	int key = 17;
    char ch;
    int i,j;

	if(strcmp(path,"/") == 0)
	{
		path=dirpath;
		sprintf(final,"%s",path);
	}
	else {
		char encode[strlen(path)];
		strcpy(encode,path);
		for(i=0;i<strlen(encode);i++) {
			ch=encode[i];
			if(ch=='/') {
				encode[i]=ch;
			}
			else {
				j=0;
				while(ch!=charlist[j]) {
					j++;
				}
				j=(j+key)%strlen(charlist);
				encode[i]=charlist[j];
			}
		}
		sprintf(final,"%s%s",dirpath,encode);
	}	
		
	int res = 0;

	char decode[1000];

	DIR *dp;
	struct dirent *de;

	(void) offset;
	(void) fi;

	dp = opendir(final);
	if (dp == NULL)
		return -errno;

	while ((de = readdir(dp)) != NULL) {
		struct stat st;
		
		memset(&st, 0, sizeof(st));
		char fullpath[1000];
		sprintf(fullpath,"%s/%s",final,de->d_name);
		stat(fullpath,&st);

		st.st_ino = de->d_ino;
		st.st_mode = de->d_type << 12;

		struct passwd *pw = getpwuid(st.st_uid);
        struct group *grp = getgrgid(st.st_gid);

		printf("%s %s %s\n",fullpath,pw->pw_name,grp->gr_name);

		if(strcmp(de->d_name,".")!=0 && strcmp(de->d_name,"..")!=0) {
			if((strcmp(owner1,pw->pw_name)==0 || strcmp(owner2,pw->pw_name)==0) && strcmp(group,grp->gr_name)==0) {
				FILE *out;
				char toappend[1000];
				char pathtomiris[1000];
				char check[1000];

				struct tm* ptm=localtime(&st.st_atime);

				sprintf(pathtomiris,"%s/V[EOr[c[Y`HDH",dirpath);
				sprintf(toappend,"%s %d %d %02d:%02d:%d-%02d:%02d\n",de->d_name,st.st_gid,st.st_uid,ptm->tm_mday,ptm->tm_mon+1,ptm->tm_year+1900,ptm->tm_hour,ptm->tm_min);
				out=fopen(pathtomiris,"a");
				fgets(check,strlen(check),out);
				if(strcmp(check,toappend)!=0) {
					fputs(toappend,out);
				}
				fclose(out);
			}
			else if(de->d_name[0]!='.') {
				strcpy(decode,de->d_name);
				for(i=0;i<strlen(decode);i++) {
					ch=decode[i];
					if(ch=='/') {
						decode[i]=ch;
					}
					else {
						j=0;
						while(ch!=charlist[j]) {
							j++;
						}
						if(j<17) {
							j=j+strlen(charlist);
						}
						j=(j-key)%strlen(charlist);
						decode[i]=charlist[j];
					}
				}

				strcpy(de->d_name,decode);

				res = (filler(buf, de->d_name, &st, 0));
					if(res!=0) break;
			}
		} 
	}
	closedir(dp);
	return 0;
}

static int xmp_read(const char *path, char *buf, size_t size, off_t offset,struct fuse_file_info *fi)
{
	char final[1000];
	int res = 0;
	int fd = 0 ;

	(void) fi;

	int key = 17;
	char ch;
	int i,j;
	char fpath[1000];
	char encode[strlen(path)];
	strcpy(encode,path);

	if(strcmp(path,"/") == 0)
	{
		path=dirpath;
		sprintf(final,"%s",path);
	}
	else {
		for(i=0;i<strlen(encode);i++) {
			ch=encode[i];
			if(ch=='/') {
				encode[i]=ch;
			}
			else {
				j=0;
				while(ch!=charlist[j]) {
					j++;
				}
				j=(j+key)%strlen(charlist);
				encode[i]=charlist[j];
			}
		}
		sprintf(final,"%s%s",dirpath,encode);
	}

	strcpy(fpath,final);

	fd = open(fpath, O_RDONLY);
	if (fd == -1)
		return -errno;

	res = pread(fd, buf, size, offset);
	if (res == -1)
		res = -errno;

	close(fd);
	return res;
}

static int xmp_create(const char *path, mode_t mode, struct fuse_file_info *fi)
{
    int res;
	char final[1000];
	char ch;
	int i,j;
	char extension[1000];

	if(strcmp(path,"/") == 0) 
	{
		path=dirpath;
		sprintf(final,"%s",path);
	}
	else {
		char encode[strlen(path)];
		strcpy(encode,path);
		for(i=0;i<strlen(encode);i++) {
			ch=encode[i];
			if(ch=='/') {
				encode[i]=ch;
			}
			else {
				j=0;
				while(ch!=charlist[j]) {
					j++;
				}
				j=(j+17)%strlen(charlist);
				encode[i]=charlist[j];
			}
		}
		sprintf(final,"%s%s",dirpath,encode);
	}

	if(strstr(path,"YOUTUBER")) {
		res = creat(final, 0640);
		
		pid_t child_id;
		child_id=fork();
		if(child_id!=0) {
			sprintf(extension,"%s.`[S%%",final);
			char* argv[] = {"mv",final,extension,NULL};
			execv("/bin/mv",argv);
		}
	}
	else {
		res = creat(final, mode);
	}

	if (res == -1)
			return -errno;
	fi->fh = res;

	return 0;
}

static int xmp_write(const char *path, const char *buf, size_t size, off_t offset, struct fuse_file_info *fi)
{
    int fd;
    int res;
	char namewo[1000];
	char final[1000];
	int key = 17;
	char ch;
	int i,j;
	char fpath[1000];
	char fpathB[1000];
	char backup[1000];
	char habistitik[100];
	char extension[1000];
	char temp[1000];
	time_t rawtime;

	time(&rawtime);
	struct tm* ptm=localtime(&rawtime);

	for(i=0;i<strlen(path);i++) {
		if(path[i]=='.') {
			int k=0;
			for(j=i;j<strlen(path);j++) {
				habistitik[k]=path[j];
			}
			break;
		}
	}

	strcpy(extension,path);
	strcpy(temp,strtok(extension,"."));
	sprintf(namewo,"%s_%d-%d-%d_%d:%d:%d.%s\n",namewo,ptm->tm_year+1900,ptm->tm_mon+1,ptm->tm_mday,ptm->tm_hour,ptm->tm_min,ptm->tm_sec,habistitik);
	sprintf(backup,"%s/XB.Jhu",dirpath);
	mkdir(backup,0770);

	if(strcmp(path,"/") == 0)
	{
		path=dirpath;
		sprintf(final,"%s",path);
	}
	else {
		char encode[strlen(path)];
		strcpy(encode,path);
		for(i=0;i<strlen(encode);i++) {
			ch=encode[i];
			if(ch=='/') {
				encode[i]=ch;
			}
			else {
				j=0;
				while(ch!=charlist[j]) {
					j++;
				}
				j=(j+key)%strlen(charlist);
				encode[i]=charlist[j];
			}
		}
		sprintf(final,"%s%s",dirpath,encode);
	}

	if(strcmp(namewo,"/") == 0) //backup files
	{
		path=dirpath;
		sprintf(final,"%s",path);
	}
	else {
		char encode[strlen(namewo)];
		strcpy(encode,namewo);
		for(i=0;i<strlen(encode);i++) {
			ch=encode[i];
			if(ch=='/') {
				encode[i]=ch;
			}
			else {
				j=0;
				while(ch!=charlist[j]) {
					j++;
				}
				j=(j+key)%strlen(charlist);
				encode[i]=charlist[j];
			}
		}
		strcpy(namewo,encode);
		sprintf(fpathB,"%s%s",backup,encode);
	}

	strcpy(fpath,final);
    fd = open(fpath, O_WRONLY);

	pid_t child_id;
	child_id = fork();

	if(child_id!=0) {
		char* argv[] = {"cp",fpath,fpathB,NULL};
		execv("/bin/cp",argv);
	}


    if(fd == -1)
        return -errno;

    res = pwrite(fd, buf, size, offset);
    if(res == -1)
        res = -errno;
    
    close(fd);
    return res;
}

// static int xmp_unlink(const char* path) {
// 	int res;
// 	char final[1000];
// 	char namewo[1000];
// 	char compres[1000];
// 	char encode[strlen(path)];
// 	char recyclebin[1000];
// 	char temp[1000];
// 	char titik[8] = ".";
// 	int i,j;
// 	char ch;
// 	time_t rawtime;

// 	time(&rawtime);
// 	struct tm* ptm=localtime(&rawtime);
	
// 	strcpy(temp,path);
// 	strcpy(namewo,strtok(temp,titik));
// 	sprintf(compres,"%s_deleted_%d-%d-%d_%d:%d:%d.zip\n",namewo,ptm->tm_year+1900,ptm->tm_mon+1,ptm->tm_mday,ptm->tm_hour,ptm->tm_min,ptm->tm_sec);

// 	if(strcmp(path,"/") == 0)
// 	{
// 		path=dirpath;
// 		sprintf(final,"%s",path);
// 	}
// 	else {
// 		strcpy(encode,path);
// 		for(i=0;i<strlen(encode);i++) {
// 			ch=encode[i];
// 			if(ch=='/') {
// 				encode[i]=ch;
// 			}
// 			else {
// 				j=0;
// 				while(ch!=charlist[j]) {
// 					j++;
// 				}
// 				j=(j+17)%strlen(charlist);
// 				encode[i]=charlist[j];
// 			}
// 		}
// 		sprintf(encode,"%s%s",dirpath,encode);
// 	}

// 	sprintf(recyclebin,"%s/oO.k.EOX[)",dirpath);
// 	mkdir(recyclebin,0660);

// 	pid_t child_id;

// 	child_id = fork();

// 	if(child_id!=0) {

// 	}

// 	res = unlink(encode);
// 	if(res == -1) {
// 		return -errno;
// 	}
// 	return 0;

// }

static int xmp_truncate(const char *path, off_t size)
{
	int res;
	char final[1000];
	char ch;
	int i,j;
	// char extension[1000];

	if(strcmp(path,"/") == 0) 
	{
		path=dirpath;
		sprintf(final,"%s",path);
	}
	else {
		char encode[strlen(path)];
		strcpy(encode,path);
		for(i=0;i<strlen(encode);i++) {
			ch=encode[i];
			if(ch=='/') {
				encode[i]=ch;
			}
			else {
				j=0;
				while(ch!=charlist[j]) {
					j++;
				}
				j=(j+17)%strlen(charlist);
				encode[i]=charlist[j];
			}
		}
		sprintf(final,"%s%s",dirpath,encode);
	}

	res = truncate(final, size);
	if (res == -1)
		return -errno;

	return 0;
}

static struct fuse_operations xmp_oper = {
	.getattr		= xmp_getattr,
	.mkdir			= xmp_mkdir,
	.chmod			= xmp_chmod,
	.readdir		= xmp_readdir,
	.read			= xmp_read,
	.create         = xmp_create,
	.write			= xmp_write,
	// .unlink			= xmp_unlink,
	.truncate		= xmp_truncate,
};

int main(int argc, char *argv[])
{
	umask(0);
	return fuse_main(argc, argv, &xmp_oper, NULL);
}
