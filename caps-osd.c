#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <xosd.h>

int main (int argc, char *argv[]) {

	FILE *fp;
	fp = fopen("/tmp/capser", "r");
	if (fp != NULL) {
		char pidstr[10];
		if (fgets(pidstr, 9, fp) == NULL) {
			exit(1);
		}
		printf("Read PID string %s\n", pidstr);
		int pid = atoi(pidstr);
		kill(pid, SIGINT);
		fclose(fp);
		remove("/tmp/capser");

		exit(0);
	}
	
	pid_t pid = fork();
	if (pid == 0) {
		xosd *osd;
		
		osd = xosd_create (2);

		if (osd == NULL) {
			perror ("Could not create \"osd\"");
			exit (1);
		}

		xosd_display(osd, 0, XOSD_string, "Capslock is ON");

		xosd_set_font(osd, "-*-arial black-*-*-*-*-*-350-*-*-*-*-*-*");

		xosd_set_pos(osd, XOSD_bottom);
		xosd_set_align(osd, XOSD_center);

		while (1) {
			sleep(4);
		}

		xosd_destroy(osd);
	
	} else {
		fp = fopen("/tmp/capser", "w");
		char pidstr[10];
		sprintf(pidstr, "%d", pid);
		fputs((char *)&pidstr, fp);
		fclose(fp);

		exit(0);
	}

	exit(0);
}
