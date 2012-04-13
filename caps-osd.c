#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <xosd.h>

xosd *osd;

int osd_shown = 0;

void toggleOSD(int s) {
	if (osd_shown) {
		xosd_hide(osd);
		osd_shown = 0;
	} else {
		xosd_show(osd);
		osd_shown = 1;
	}
}

void registerSignal() {
	struct sigaction sigHandler;

	sigHandler.sa_handler = toggleOSD;
	sigemptyset(&sigHandler.sa_mask);
	sigHandler.sa_flags = 0;

	sigaction(SIGUSR1, &sigHandler, NULL);
}

int main (int argc, char *argv[]) {
	registerSignal();

	osd = xosd_create (2);

	if (osd == NULL) {
		perror ("Could not create \"osd\"");
		exit (1);
	}

	xosd_display(osd, 0, XOSD_string, "Capslock is ON");

	xosd_set_font(osd, "-*-arial black-*-*-*-*-*-350-*-*-*-*-*-*");

	xosd_set_pos(osd, XOSD_bottom);
	xosd_set_align(osd, XOSD_center);
	xosd_hide(osd);

	while (1) {
		sleep(1);
	}

	return 0;
}
