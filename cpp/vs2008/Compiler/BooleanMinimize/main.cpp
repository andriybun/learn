#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
#include<conio.h>
//#include<alloc.h>

typedef struct el {int konst,gr,mint[3],flag;
	           struct el *a_v, *a_n;} STEK;
typedef struct elm {int konst[4],gr,var[2],lev,flag;
	           struct elm *a_v, *a_n;} CTK2;
typedef struct el_sp {int val;
	           struct el_sp *a_v, *a_n;} CTEK;
CTEK *www, *wwp;
STEK *ko1,*ko2,*kostart;
CTK2 *glue1, *glue2,*gluestart,*gl1,*gl2,*glst;
char *bin="000001010011100101110111";
int x,y,z,num,value,dnform[80],dnfmax,not1=0,not2=0,not4=0,ones=0,iamtheone;
char impl[80];
int *implic,i,j,flags[8],fl=0;
char form[80],polzap[80],dnf[80],sdnf[80];
void E(void);
void T(void);
void F(void);
void DNF(void);
void error(int);
void minimize(void);
void minimize2(void);
void form_CTEK(void);
void matrix(void);
void final(int);
int check(void);
void zero(void);
void finish(void);
void prn(void);
void transformer(void);
int k_el(void);

void error(int code)
 {
  switch (code)
         {
	  case 1: printf ("èéåàãäÄ! (%d) èpoØ„Èe≠o ')'!",num);
	  case 2: printf ("èéåàãäÄ! He¢i§o¨®© c®¨¢o´ '%c'!",form[num]);
	  case 3: printf ("èéåàãäÄ! èpoØ„Èe≠o 'V', '^' a°o '!'!");
         }
  printf("\nîop¨„´a ≠eØpa¢®´Ï≠a!\n");
  printf("H†‚®·≠i‚Ï °„§Ï Ô™„ ™´†¢iË„!");
  exit(1);
 }

void E(void)
 {
  char znak=' ';
  T();
  if (form[num]=='v') form[num]='V';
  while (form[num]=='V'||form[num]=='v')
        {
         if (form[num]=='v') form[num]='V';
         znak=form[num++];
         T();
         polzap[strlen(polzap)]=znak;
        }
 }

void T(void)
 {
  char znak=' ';
  F();
  while (form[num]=='^')
        {
         znak='^'; num++;
         F();
         polzap[strlen(polzap)]=znak;
        }
 }

void F(void)
 {
  char znak=' ';
  if (form[num]=='!') znak=form[num++];
  if (form[num]=='x'||form[num]=='y'||form[num]=='z') polzap[strlen(polzap)]=form[num++];
  else if (form[num]=='X'||form[num]=='Y'||form[num]=='Z') polzap[strlen(polzap)]=tolower(form[num++]);
  else if (form[num]=='(')
          {
           num++;
           E();
           if (form[num]!=')') error(1);
           else num++;
  }
  else if(form[num]=='!') E();
  else error(2);
  if (znak=='!') strcat(polzap,"!");
 }

void DNF(void)
 {
  int flag0=0,flag1=0,dnformlich=0;
  dnf[0]='\0';
  for (x=0;x<=1;x++)
      for (y=0;y<=1;y++)
          for (z=0;z<=1;z++)
             {
              www=(CTEK *)malloc(sizeof(CTEK));
              www->a_v=NULL;
              www->a_n=NULL;
              for (num=0;num<strlen(polzap);num++)
                  {
                   if ((polzap[num]>='x')&&(polzap[num]<='z'))
                      {
                       switch (polzap[num])
                              {
                               case 'x': www->val=x; break;
                               case 'y': www->val=y; break;
                               case 'z': www->val=z; break;
                              }
                       wwp=(CTEK *)malloc(sizeof(CTEK));
                       www->a_v=wwp;
                       wwp->a_n=www;
                       wwp->a_v=NULL;
                       www=wwp;
                      }
                   else if (polzap[num]=='!')
                           {
                            www->a_n->val=1-www->a_n->val;
                           }
                   else if (polzap[num]=='^')
                           {
                            www=www->a_n;
                            www->a_n->val=www->a_n->val*www->val;
                            www->a_v=NULL;
                            free(wwp);
                            wwp=www;
                           }
                   else if (polzap[num]=='V')
                           {
                            www=www->a_n;
                            www->a_n->val=www->a_n->val+www->val-(www->a_n->val*www->val);
                            www->a_v=NULL;
                            free(wwp);
                            wwp=www;
                           }
                  }
              if (www->a_n->val==1)
                 {
                  flag1=1;
                  ones++;
                  dnform[dnformlich++]=x;
                  dnform[dnformlich++]=y;
                  dnform[dnformlich++]=z;
                  if (x==0) strcat(dnf,"!x"); else strcat(dnf,"x");
                  if (y==0) strcat(dnf,"!y");  else strcat(dnf,"y");
                  if (z==0) strcat(dnf,"!z V ");else strcat(dnf,"z V ");
                 }
              if (www->a_n->val==0) flag0=1;
              free(www->a_n);free(www);
             }
  if (flag0==0) {printf("Function is const = 1\n");fl=1;}
  else if (flag1==0) {printf("Function is const = 0\n");fl=1;}
  else {dnf[strlen(dnf)-2]='\0'; printf("ÑHî:  %s\n",dnf); dnfmax=dnformlich; minimize();}
 }

void form_CTEK(void)
 {
  int kons,g,m,dnformlich;
  STEK *kuku;
  for (dnformlich=0;dnformlich<dnfmax;dnformlich++)
      {
       x=dnform[dnformlich++];
       y=dnform[dnformlich++];
       z=dnform[dnformlich];
       if (ko1==NULL)
          {
           ko1=(STEK *)malloc(sizeof(STEK));
           ko1->a_v=NULL; ko1->a_n=NULL;
           kostart=kuku=ko1;
           ko1->flag=0;
           ko1->konst=x*4+y*2+z*1; ko1->gr=x+y+z;
           ko1->mint[0]=x; ko1->mint[1]=y; ko1->mint[2]=z;
          }
       else
          {
           ko2=(STEK *)malloc(sizeof(STEK));
           ko2->a_v=NULL; ko2->a_n=ko1; ko1->a_v=ko2;
           ko2->konst=x*4+y*2+z*1; ko2->gr=x+y+z;
           ko2->mint[0]=x; ko2->mint[1]=y; ko2->mint[2]=z;
           kuku=ko2; ko2->flag=0;
           while ((ko1!=NULL)&&(ko2!=NULL)&&(ko2->gr)<(ko1->gr))
                 {
                  kons=ko1->konst; ko1->konst=ko2->konst; ko2->konst=kons;
                  g=ko1->gr; ko1->gr=ko2->gr; ko2->gr=g;
                  m=ko1->mint[0]; ko1->mint[0]=ko2->mint[0]; ko2->mint[0]=m;
                  m=ko1->mint[1]; ko1->mint[1]=ko2->mint[1]; ko2->mint[1]=m;
                  m=ko1->mint[2]; ko1->mint[2]=ko2->mint[2]; ko2->mint[2]=m;
                  ko2=ko1; if (ko1->a_n!=NULL) ko1=ko1->a_n;
                 }
          }
       ko2=kuku;
       ko1=ko2;
      }
 }

void minimize(void)
 {
  int koko;
  STEK *kkkk,*kuku;
  ko1=NULL;
  form_CTEK();
  ko1=kostart;
  while (ko1->a_v!=NULL) ko1=ko1->a_v;
  kuku=kostart;
  ko1=kuku->a_v;
  glue1=NULL;
  while (kuku!=NULL)
   {
    while (ko1!=NULL)
        {
         if (((ko1->gr-kuku->gr)==1)&&(((ko1->konst-kuku->konst)==1)
             ||((ko1->konst-kuku->konst)==2)||((ko1->konst-kuku->konst)==4)))
            {
             koko=ko1->konst-kuku->konst;
             if (glue1==NULL)
                {
                 ko1->flag=kuku->flag=1;
                 glue1=(CTK2*)malloc(sizeof(CTK2));
                 gluestart=glue1;
                 glue1->a_n=glue1->a_v=NULL;
                 glue1->konst[0]=kuku->konst; glue1->konst[1]=ko1->konst;
                 glue1->konst[2]=glue1->konst[3]=-1;
                 glue1->gr=kuku->gr;
                 switch (koko)
                        {case 1: glue1->var[0]=2; break;
                         case 2: glue1->var[0]=1; break;
                         case 4: glue1->var[0]=0; break;}
                 glue1->flag=0;
                }
             else
                {
                 ko1->flag=kuku->flag=1;
                 glue2=(CTK2*)malloc(sizeof(CTK2));
                 glue2->a_v=NULL; glue1->a_v=glue2; glue2->a_n=glue1; glue1=glue2;
                 glue2->konst[0]=kuku->konst; glue2->konst[1]=ko1->konst;
                 glue2->konst[2]=glue2->konst[3]=-1;
                 glue2->gr=kuku->gr;
                 switch (koko)
                        {case 1: glue1->var[0]=2; break;
                         case 2: glue1->var[0]=1; break;
                         case 4: glue1->var[0]=0; break;}
                 glue2->flag=0;
                }
             ko1=ko1->a_v;
            }
         else ko1=ko1->a_v;
        }
    kuku=kuku->a_v;
    if (kuku!=NULL) ko1=kuku->a_v;
   }
 }

typedef struct element {char mdnf[80];
	           struct element *a_v, *a_n;} CMYK;
CMYK *f1, *f2;

void minimize2(void)
 {
  int koko,tmp1,tmp2;
  CTK2 *kkkk,*kuku;
  glue1=kuku=gluestart;
  glue1=kuku->a_v;
  gl1=NULL;
  while (kuku!=NULL)
   {
    while (glue1!=NULL)
        {
         tmp1=(glue1->konst[0]-kuku->konst[0]);
         tmp2=(glue1->konst[1]-kuku->konst[1]);
         if (((glue1->gr-kuku->gr)==1)&&(tmp1==tmp2)&&((tmp1==1)||(tmp1==2)||(tmp1==4)))
            {
             if (gl1==NULL)
                {
                 glue1->flag=kuku->flag=1;
                 gl1=(CTK2*)malloc(sizeof(CTK2));
                 glst=gl1;
                 gl1->a_n=gl1->a_v=NULL;
                 gl1->konst[0]=kuku->konst[0];
                 if (kuku->konst[1]>glue1->konst[0])
                    {gl1->konst[1]=glue1->konst[0]; gl1->konst[2]=kuku->konst[1];}
                 else {gl1->konst[1]=kuku->konst[1]; gl1->konst[2]=glue1->konst[0];}
                 gl1->konst[3]=glue1->konst[1];
                 gl1->gr=kuku->gr;
                 gl1->var[0]=kuku->var[0];
                 switch (tmp1)
                        {case 1: gl1->var[1]=2; break;
                         case 2: gl1->var[1]=1; break;
                         case 4: gl1->var[1]=0; break;}
                }
             else
                {
                 glue1->flag=kuku->flag=1;
                 gl2=(CTK2*)malloc(sizeof(CTK2));
                 gl2->a_v=NULL; gl1->a_v=gl2; gl2->a_n=gl1; gl1=gl2;
                 gl1->konst[0]=kuku->konst[0];
                 if (kuku->konst[1]>glue1->konst[0])
                    {gl1->konst[1]=glue1->konst[0]; gl1->konst[2]=kuku->konst[1];}
                 else {gl1->konst[1]=kuku->konst[1]; gl1->konst[2]=glue1->konst[0];}
                 gl1->konst[3]=glue1->konst[1];
                 kkkk=glst;
                 while (kkkk!=NULL&&kkkk!=gl1)
                       {
                        if ((kkkk->konst[0]==gl1->konst[0])&&(kkkk->konst[1]==gl1->konst[1])
                          &&(kkkk->konst[2]==gl1->konst[2])&&(kkkk->konst[3]==gl1->konst[3]))
                           {gl1=gl1->a_n; free(gl1->a_v); gl1->a_v=NULL; kkkk=NULL;gl2=gl1;}
                        else {kkkk=kkkk->a_v;
                              gl1->gr=kuku->gr;
                              gl1->var[0]=kuku->var[0];
                              switch (tmp1)
                                     {case 1: gl1->var[1]=2; break;
                                      case 2: gl1->var[1]=1; break;
                                      case 4: gl1->var[1]=0; break;}
                                      glue2->lev=1;}
                       }
                }
             glue1=glue1->a_v;
            }
         else glue1=glue1->a_v;
        }
    kuku=kuku->a_v;
    if (kuku!=NULL) glue1=kuku->a_v; else glue1=kuku;
   }
 }

void prn(void)
 {
  ko1=kostart;
  printf("\n[%d]: - %d\n",ko1->konst,ko1->flag);
  if (ko1->flag==0) not1++;
  while (ko1->a_v!=NULL)
        {
         ko1=ko1->a_v;
         if (ko1->flag==0) not1++;
	 printf("[%d]: - %d\n",ko1->konst,ko1->flag);
        }
  if (gluestart!=NULL)
 	 {glue1=gluestart;
	  if (glue1!=NULL)
	     {
   	   printf("[%d,%d]: (%d) - %d\n",glue1->konst[0],glue1->konst[1],glue1->var[0],glue1->flag);
	      if (glue1->flag==0) not2++;
	      while (glue1->a_v!=NULL)
   	     {
      	   glue1=glue1->a_v;
         	if (glue1->flag==0) not2++;
		 printf("[%d,%d]: (%d) - %d\n",glue1->konst[0],glue1->konst[1],glue1->var[0],glue1->flag);
   	     }
        }
     }
  if (glst!=NULL)
    {gl1=glst;
	  if (gl1!=NULL)
	     {
   	   printf("[%d,%d,%d,%d]: (%d,%d)\n",gl1->konst[0],gl1->konst[1],gl1->konst[2],gl1->konst[3],gl1->var[0],gl1->flag);
   	   not4++;
	      while (gl1->a_v!=NULL)
	        {
   	      gl1=gl1->a_v;
      	   not4++;
			   printf("[%d,%d,%d,%d]: (%d,%d)\n",gl1->konst[0],gl1->konst[1],gl1->konst[2],gl1->konst[3],gl1->var[0],gl1->flag);
	        }
   	  }
    }
 }

void matrix(void)
 {
  int ii,lim;
  implic=(int*)malloc((not1+not2+not4+1)*8*sizeof(int));
  for (num=8;num<8*(not1+not2+not4+1);num++) implic[num]=0;
  for (num=0;num<8;num++) implic[num]=-1;
  iamtheone=not1+not2+not4;
  ko1=kostart;
  num=1;
  if (ko1->flag==0) {implic[ko1->konst]=ko1->konst;
                     implic[8*num+ko1->konst]=1;
                     *(impl+3*num)=bin[3*ko1->konst];
                     *(impl+3*num+1)=bin[3*ko1->konst+1];
                     *(impl+3*num+2)=bin[3*ko1->konst+2];
                     num++;}
  while (ko1->a_v!=NULL)
        {
         ko1=ko1->a_v;
         if (ko1->flag==0) {implic[ko1->konst]=ko1->konst;
                            implic[8*num+ko1->konst]=1;
                            *(impl+3*num)=bin[3*ko1->konst];
                            *(impl+3*num+1)=bin[3*ko1->konst+1];
                            *(impl+3*num+2)=bin[3*ko1->konst+2];
                            num++;}}
  if (gluestart!=NULL)
  {glue1=gluestart;
  if (glue1!=NULL)
     {if (glue1->flag==0) {implic[glue1->konst[0]]=glue1->konst[0];
                           implic[glue1->konst[1]]=glue1->konst[1];
                           implic[8*num+glue1->konst[0]]=1;
                           implic[8*num+glue1->konst[1]]=1;
                           *(impl+3*num)=bin[3*glue1->konst[0]];
                           *(impl+3*num+1)=bin[3*glue1->konst[0]+1];
                           *(impl+3*num+2)=bin[3*glue1->konst[0]+2];
                           *(impl+3*num+glue1->var[0])='-';
                           num++;}
      while (glue1->a_v!=NULL)
        {
         glue1=glue1->a_v;
         if (glue1->flag==0) {implic[glue1->konst[0]]=glue1->konst[0];
                              implic[glue1->konst[1]]=glue1->konst[1];
                              implic[8*num+glue1->konst[0]]=1;
                              implic[8*num+glue1->konst[1]]=1;
                              *(impl+3*num)=bin[3*glue1->konst[0]];
                              *(impl+3*num+1)=bin[3*glue1->konst[0]+1];
                              *(impl+3*num+2)=bin[3*glue1->konst[0]+2];
                              *(impl+3*num+glue1->var[0])='-';
                              num++;}}
     }}
  if (gluestart!=NULL)
  {gl1=glst;
  if (gl1!=NULL)
     {
      implic[gl1->konst[0]]=gl1->konst[0];
      implic[gl1->konst[1]]=gl1->konst[1];
      implic[gl1->konst[2]]=gl1->konst[2];
      implic[gl1->konst[3]]=gl1->konst[3];
      implic[8*num+gl1->konst[0]]=1;
      implic[8*num+gl1->konst[1]]=1;
      implic[8*num+gl1->konst[2]]=1;
      implic[8*num+gl1->konst[3]]=1;
      *(impl+3*num)=bin[3*gl1->konst[0]];
      *(impl+3*num+1)=bin[3*gl1->konst[0]+1];
      *(impl+3*num+2)=bin[3*gl1->konst[0]+2];
      *(impl+3*num+gl1->var[0])='-';
      *(impl+3*num+gl1->var[1])='-';
      num++;
      while (gl1->a_v!=NULL)
        {gl1=gl1->a_v;
         implic[gl1->konst[0]]=gl1->konst[0];
         implic[gl1->konst[1]]=gl1->konst[1];
         implic[gl1->konst[2]]=gl1->konst[2];
         implic[gl1->konst[3]]=gl1->konst[3];
         implic[8*num+gl1->konst[0]]=1;
         implic[8*num+gl1->konst[1]]=1;
         implic[8*num+gl1->konst[2]]=1;
         implic[8*num+gl1->konst[3]]=1;
         *(impl+3*num)=bin[3*gl1->konst[0]];
         *(impl+3*num+1)=bin[3*gl1->konst[0]+1];
         *(impl+3*num+2)=bin[3*gl1->konst[0]+2];
         *(impl+3*num+gl1->var[0])='-';
         *(impl+3*num+gl1->var[1])='-';
         num++;}
     }}
//  clrscr();
  printf("\nI¨Ø´i™a≠‚≠a ¨a‚p®ÊÔ:\n\n   …");
  lim=(ones+1)*8;
  for (ii=1;ii<lim;ii++) if ((ii%8)!=0)  printf("Õ"); else printf("À");
  printf("ª");
  for (i=0;i<num;i++)
      {
       if (i!=0)
   	  {printf("\n   ∫"); for (ii=1;ii<lim;ii++) if ((ii%8)!=0)  printf("Õ"); else printf("Œ");
	      printf("π\n   ∫  %c%c%c  ∫",*(impl+i*3),*(impl+i*3+1),*(impl+i*3+2));
         for (j=0;j<8;j++) if (implic[j]>=0) if (implic[8*i+j]||(i==0&&j==0)) printf("   %d   ∫",implic[8*i+j]);
                           else printf("       ∫");}
       else {printf("\n   ∫       ∫");
             for (j=0;j<8;j++)
                 if (implic[j]>=0)
                    printf("  %c%c%c  ∫",*(bin+3*j),*(bin+3*j+1),*(bin+3*j+2));}
      }
  printf("\n   »");
  for (ii=1;ii<lim;ii++) if ((ii%8)!=0)  printf("Õ"); else printf(" ");
  printf("º\n");
 }

void final(int par)
 {
  int ab,cd,ef,gh,prapor;
  char st[3];
  for (ab=par+1;ab<=iamtheone;ab++)
      {
       for(cd=0;cd<8;cd++)
          {
           if (implic[8*ab+cd]&&!flags[cd]) flags[cd]=ab;
          }
       if (check())
          {for (ef=0;ef<8;ef++)
               {strncpy(st,(impl+3*flags[ef]),3);
                prapor=0;
                for (gh=0;gh<strlen(f1->mdnf);gh+=3) if (!strncmp(f1->mdnf+gh,st,3)) prapor=1;
                if (!prapor) strncat(f1->mdnf,st,3);
                if (flags[ef]==ab) flags[ef]=0;}
           f2=(CMYK*)malloc(sizeof(CMYK));
           f1->a_v=f2; f2->a_n=f1; f2->a_v=NULL; f2->mdnf[0]='\0';
           f1=f2;}
       else {final(ab);
             for(cd=0;cd<8;cd++) if (flags[cd]==ab) flags[cd]=0;}
      }
 }

void finish (void)
 {
  int ab,cd,ef,minnum;
  minnum=k_el();
  while (f1->a_n!=NULL) {f1=f1->a_n;
                         if (k_el()<minnum) f1->a_v=NULL;
                         else if (k_el()>minnum) {if (f1->a_n!=NULL)
                                                     {f2=f1->a_n; f1->a_v->a_n=f2;
                                                      f2->a_v=f1->a_v;
                                                      free(f1); f1=f2->a_v;}
                                                  else {f2=f1->a_v; f2->a_n=NULL;
                                                      free(f1); f1=f2;}}}
  transformer();
  printf("%s\n",f1->mdnf);
  while (f1->a_v!=NULL) {f1=f1->a_v; transformer(); printf("%s\n",f1->mdnf);}
 }

void transformer(void)
 {int ab;
  char st[3];
  for (ab=0;ab<strlen(f1->mdnf);ab+=3)
      {strncpy(st,(f1->mdnf+ab),3);
       switch (st[0])
              {case '-': break;
               case '0': strcat(sdnf,"!x"); break;
               case '1': strcat(sdnf,"x"); break;}
       switch (st[1])
              {case '-': break;
               case '0': strcat(sdnf,"!y"); break;
               case '1': strcat(sdnf,"y"); break;}
       switch (st[2])
              {case '-': break;
               case '0': strcat(sdnf,"!z"); break;
               case '1': strcat(sdnf,"z"); break;}
       strcat(sdnf," V ");}
   sdnf[strlen(sdnf)-2]='\0';
   strcpy(f1->mdnf,sdnf);
   sdnf[0]='\0';
 }

int k_el(void)
 {
  int ii,kel=0;
  for (ii=0;ii<strlen(f1->mdnf);ii++) if (f1->mdnf[ii]!='-') kel++;
  return kel;
 }

void zero(void)
 {
  int ii=0;
  for (;ii<8;ii++) flags[ii]=0;
 }

int check(void)
 {
  int ii=0;
  for (ii=0;ii<8;ii++)
      {
       if (flags[ii]==0&&implic[ii]!=-1) return 0;
      }
  return 1;
 }

int main(void)
 {
  int iii;
//  clrscr();
  printf("\n");
  for (iii=0;iii<15;iii++) printf("*");
  printf(" Program for minimization of boolean expressions ");
  for (iii=0;iii<15;iii++) printf("*");
  printf("\n");
  printf("Enter expression:  ");
  scanf("%s",&form);
  num=0;
  sdnf[0]='\0';
  E();
  if (form[num]!='\0') error(3);
  DNF();
  getch();
  if(!fl)
  {if (gluestart!=NULL) minimize2();
  f1=(CMYK*)malloc(sizeof(CMYK));
  f1->a_v=f1->a_n=NULL; f1->mdnf[0]='\0';
  printf("C™´eÓ¢a≠≠Ô:\n");
  prn();
  getch();
  matrix();
  zero();
  final(0);
  f1=f1->a_n; free(f2); f1->a_v=NULL; f2=f1;
  printf("\nåÑçî:\n\n");
  finish();}
  printf("\nH†‚®·≠i‚Ï °„§Ï Ô™„ ™´†¢iË„!");
  getch();
 }
