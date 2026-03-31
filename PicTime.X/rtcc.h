#ifndef RTCC_H
#define	RTCC_H

void initRtcc();
void writeTimeRtcc(unsigned char* );
void writeDateRtcc(unsigned char* );
void readTimeRtcc(unsigned char* );
void readDateRtcc(unsigned char* );
void readTimeCharRtcc(char* );
void readDateCharRtcc(char* );
void readTimeTimehRtcc(struct tm *t);

#endif	/* RTCC_H */