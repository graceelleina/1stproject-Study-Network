#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <conio.h>
#include <time.h>

char usernameInput[115];
int banyakTeman = 1;

struct userList
{
    char username[30];
    userList *next;
} * headList, *tailList, *currList;

userList *createUserList(char *string)
{
    userList *newUser = (userList *)malloc(sizeof(userList));
    strcpy(newUser->username, string);
    newUser->next = NULL;
    return newUser;
}

void pushTail(char *string)
{
    userList *temp = createUserList(string);
    if (!headList)
    {
        headList = tailList = temp;
    }
    else
    {
        tailList->next = temp;
        tailList = temp;
    }
}

bool isUnique(char *string)
{
    FILE *fp;
    int n;
    char curr[30];
    bool flag = true;

    fp = fopen("userList.txt", "r");
    fscanf(fp, "%d\n", &n);
    while (!feof(fp))
    {
        fscanf(fp, "%[^\n]\n", curr);
        if (!strcmp(curr, string))
        {
            flag = false;
            break;
        }
    }
    fclose(fp);

    return flag;
}

bool cekASCII(char *str)
{
    bool flag = true;
    for (int i = 0; str[i] != '\0'; i++)
    {
        if ((str[i] < 'a' && str[i] != ' ') || str[i] > 'z')
        {
            flag = false;
            break;
        }
    }
    return flag;
}

bool validate(char *string)
{
    bool flag = false;
    int len = strlen(string);
    if (len > 0 && len <= 24)
    {
        if (cekASCII(string))
        {
            flag = true;
        }
    }
    return flag;
}

void regis()
{
    char usernameInput[115];
    char passwordInput[115];

    while (true)
    {
        printf("Masukkan username [lowercase] & [1..24]: ");
        scanf("%[^\n]", usernameInput);
        getchar();
        if (validate(usernameInput))
        {
            if (isUnique(usernameInput))
            {
                break;
            }
        }
    }

    while (true)
    {
        printf("Masukkan password [lowercase] & [1..24]: ");
        scanf("%[^\n]", passwordInput);
        getchar();
        if (validate(usernameInput))
        {
            break;
        }
    }

    pushTail(usernameInput);

    FILE *fp, *fs;

    fp = fopen("userList.txt", "a");
    fprintf(fp, "\n%s", usernameInput);
    fclose(fp);

    fs = fopen("userLink.txt", "a");
    fprintf(fp, "\n%s#%s#%s.txt", usernameInput, passwordInput, usernameInput);
    fclose(fs);
}

bool login(char *address)
{
    //char usernameInput[115];
    char passwordInput[115];
    char username[30], password[30];
    bool very = false;

    printf("Username : ");
    scanf("%[^\n]", usernameInput);
    getchar();

    printf("Password : ");
    scanf("%[^\n]", passwordInput);
    getchar();

    FILE *fp;
    fp = fopen("userLink.txt", "r");

    while (!feof(fp))
    {
        fscanf(fp, "%[^#]#%[^#]#%[^\n]\n", username, password, address);
        if (!strcmp(username, usernameInput))
        {
            if (!strcmp(password, passwordInput))
            {
                very = true;
            }
            break;
        }
    }
    return very;
}

void viewawal() {
    FILE *fp;
    char user[30];
    fp = fopen("userList.txt", "r");
        while (!feof(fp))
        {
            fscanf(fp, "%[^\n]\n", user);
            pushTail(user);
        }
        fclose(fp);
    
}

void viewUserList()
{

    int num = 1;
    printf("No.     Username\n");
        currList = headList;
        if(!headList){
            printf("\n");
        }
        else
        {
            while (currList){
                printf("%d       %s\n", num++, currList->username);
                currList = currList->next;
            }
            
        }
}

void displayMainMenu()
{
    printf("Oo======================oO\n");
    printf("      STUDY NETWORK      \n");
    printf("Oo======================oO\n\n");
    printf("[All User]\n");
    viewUserList();
    printf("\n[1].Register\n");
    printf("[2].Login\n");
    printf("[3].Exit\n");
    printf("---------------------------------------\n");
    printf("Press 0 and enter to abort an operation\n");
    printf("---------------------------------------\n");
    printf(">> ");
}

void clrScr() {
    system("cls");
}

struct comment_like {
    int like;
    char comment[260];
    comment_like *next,*prev;
};

struct binTrash {
    char bin[260];
    binTrash *next,*prev;
} *h, *t;

struct Notes {
    char note[260]; //since note can taken a paragraph
    char get_time[260];
    comment_like *hlike, *tlike, *currlike;//harena setiap node ada link list comment_likenya
    Notes *next,*prev; //for make a link list notes
    int flag;
    int com;
} *head, *tail, *currNotes;

Notes *createNote(const char *note) {
    Notes *newNotes = (Notes*)malloc(sizeof(Notes));
    strcpy(newNotes->note, note);
    newNotes->next = newNotes->prev = NULL;
    newNotes->currlike = newNotes->hlike = newNotes->tlike = NULL;
    newNotes->flag = 0;
    newNotes->com = 0;
    return newNotes;
}

comment_like *createComment(Notes *temp, const char *comment) {
    // currNotes = (Notes*)malloc(sizeof(Notes));
    temp->currlike = (comment_like*)malloc(sizeof(comment_like));

    strcpy(temp->currlike->comment, comment); 
    temp->currlike->like = 0;
    temp->currlike->next = temp->currlike->prev = NULL;

    return temp->currlike;
}

binTrash *createBin(const char *bin) {
    binTrash *newBin = (binTrash*)malloc(sizeof(binTrash));
    strcpy(newBin->bin, bin);
    newBin->next = newBin->prev = NULL;
    return newBin;
}

int validasiAlphaNumeric (const char *str) {
    int result[260];
    int count=0;
    int len = strlen(str);

    for(int i=0; i<len; i++) {
        result[i] = isalnum(str[i]);
        if(result[i] || str[i]==32) {
            count++;
        }
    }

    if (count==len) return 1; //valid
    else return 0; //invalid
}

void pushNote(const char *note) {
    Notes *temp = createNote(note);

    if(!head) {
        head = tail = temp;
    }
    else {
        head->prev = temp;
        temp->next = head;
        head = temp;
    }
}

void pushComment(Notes *temp, const char *comment) {

    comment_like *temps = createComment(temp, comment);
    temp->com = temp->com + 1;

    if(!temp->hlike) {
        temp->hlike = temp->tlike = temps;
    }
    else {
        temp->hlike->prev = temps;
        temps->next = temp->hlike;
        temp->hlike = temps;
    }
}

void likeComment (Notes *temp, int idx){
    temp->currlike = temp->hlike;
    int pos=1;
    while(pos!=idx){
        pos++;
        temp->currlike = temp->currlike->next;
    }
    temp->currlike->like = temp->currlike->like + 1;

}

void pushBin(const char *bin) {
    binTrash *temp = createBin(bin);

    if(!h) {
        h = t = temp;
    }
    else {
        h->prev = temp;
        temp->next = h;
        h = temp;
    }
}

void popHead() {
    if(!head) { 
        return;
    } 
    else if(head == tail) { 
        free(head);
        head = tail = NULL;
    } 
    else { 
        Notes *newHead = head->next; 
        head->next = newHead->prev = NULL; 
        free(head); 
        head = newHead; 
    }
}

void popHeadBin() {
    if(!h) { 
        return;
    } 
    else if(h == t) { 
        free(h);
        h = t = NULL;
    } 
    else { 
        binTrash *newHead = h->next; 
        h->next = newHead->prev = NULL; 
        free(h); 
        h = newHead; 
    }
}

void popTail() {
    if(!head) { 
        return; 
    } 
    else if(head == tail) { 
        free(head);
        head = tail = NULL;
    } 
    else {
        Notes *newTail = tail->prev; 
        tail->prev = newTail->next = NULL;
        free(tail);
        tail = newTail; 
    }
}

void popTailBin() {
    if(!h) { 
        return; 
    } 
    else if(h == t) { 
        free(h);
        h = t = NULL;
    } 
    else {
        binTrash *newTail = t->prev; 
        t->prev = newTail->next = NULL;
        free(t);
        t = newTail; 
    }
}

void popNote(int value) {
    int pos=1;
    Notes *curr = head;
    while(pos!=value) {
        pos++;
        curr = curr->next;
    }

    if(!head) {
        return;
    } 
    else if(strcmp(head->note, curr->note)==0) {
        pushBin(curr->note);
        popHead(); 
    } 
    else if(strcmp(tail->note, curr->note)==0) {
        pushBin(curr->note);
        popTail(); 
    } 
    else {
        pushBin(curr->note);
        curr->prev->next = curr->next; 
        curr->next->prev = curr->prev; 
        curr->prev = curr->next = NULL;
        free(curr);
        curr = NULL; 
    }
}

void popBin(int value) {
    int pos=1;
    binTrash *curr = h;
    while(pos!=value) {
        pos++;
        curr = curr->next;
    }

    if(!h) {
        return;
    } 
    else if(strcmp(h->bin, curr->bin)==0) {
        popHeadBin();
    } 
    else if(strcmp(t->bin, curr->bin)==0) {
        popTailBin(); 
    } 
    else {
        curr->prev->next = curr->next; 
        curr->next->prev = curr->prev; 
        curr->prev = curr->next = NULL;
        free(curr);
        curr = NULL; 
    }
}

void addNote() {
    char mynote[500];
    int yesno, edit, x=0;

    while(x==0) {
        clrScr();
        printf("What's on your mind?\n");
        printf(">> ");
        scanf("%[^\n]", &mynote); 
        getchar();

        int val = validasiAlphaNumeric(mynote);

        while(val!=1) {
            clrScr();
            printf("Invalid Input!!!\n");
            printf("Input must be Alphanumeric only!\n");
            printf("Please re-input\n\n");
            printf("What's on your mind?\n");
            printf(">> ");
            scanf("%[^\n]", &mynote);
            getchar();
            val = validasiAlphaNumeric(mynote);
        } 

        printf("\nAre you sure you want to post it?\n");
        printf("[1] Yes\n");
        printf("[2] No\n");
        printf(">> ");
        scanf("%d", &yesno);
        getchar();

        while(yesno<1 || yesno>2) {
            printf("\nInvalid Input!!!\n");
            printf("Please re-input\n\n");
            printf(">> ");
            scanf("%d", &yesno);
            getchar();
        }

        if(yesno==1) {
            x=1;
            pushNote(mynote);
            printf("\nYour Post Has Been Saved!!!\n");
            printf("Press Enter to Continue...");
            getchar();
            break;
        }
        else {
            printf("\nDo you want to re-write your note?\n");
            printf("[1] Yes\n");
            printf("[2] Back to menu\n");
            printf(">> ");
            scanf("%d", &edit);
            getchar();

            while(edit<1 || edit>2) {
                printf("\nInvalid Input!!!\n");
                printf("Please re-input\n\n");
                printf(">> ");
                scanf("%d", &edit);
                getchar();
            }

            if(edit==1) {
                x=0;
                continue;
            }
            else {
                x=1;
                break;
            }
        }
    }
}

void deleteNote() {
    int i=1, pilih, yesno;
    Notes *curr = head;

    clrScr();

    if(curr==NULL) {
        printf("\nThere are no notes available!\n\n");
        printf("Press enter to back to menu...");
        getchar();
        return;
    }
    else {
        printf("\nWhich note do you want to delete?\n");
        while(curr) {
            printf("[%d] %s\n", i, curr->note);
            curr = curr->next;
            i++;
        }
        printf("----------------------------------\n");
        printf("[%d] Back to menu\n", i);
        printf(">> ");
        scanf("%d", &pilih);
        getchar();

        while(pilih<1 || pilih>i) {
            printf("Invalid Input!!!\n");
            printf("Please re-input\n\n");
            printf(">> ");
            scanf("%d", &pilih);
            getchar();
        }

        if(pilih==i) {
            printf("\nPress Enter to go back to menu...");
            getchar();
            return;
        }

        printf("\nAre you sure you want to delete your post?\n");
        printf("[1] Yes\n");
        printf("[2] No\n");
        printf(">> ");
        scanf("%d", &yesno);
        getchar();

        while(yesno<1 || yesno>2) {
            printf("Invalid Input!!!\n");
            printf("Please re-input\n\n");
            printf(">> ");
            scanf("%d", &yesno);
            getchar();
        }

        if(yesno==1) {
            popNote(pilih);
            printf("\nYour Post Has Been Deleted!!!\n");
            printf("Press Enter to Continue...");
            getchar();
        }
        else {
            return;
        }
    }
}

void updateData(const char *baru, int idx) {
    if(!head){
        printf("Linked List not initialized\n");
        return;
    }

    int pos=1;
    Notes *curr = head;
    while(pos!=idx) {
        pos++;
        curr = curr->next;
    }

    strcpy(curr->note, baru);
    return;
}

void editNote() {
    int i=1, pilih, yesno;
    char newpost[260];
    Notes *curr = head;

    clrScr();

    if(curr==NULL) {
        printf("\nThere are no notes available!\n\n");
        printf("Press enter to back to menu...");
        getchar();
        return;
    }
    else {
        printf("\nWhich note do you want to edit?\n");

        while(curr) {
            printf("[%d] %s\n", i, curr->note);
            curr = curr->next;
            i++;
        }
        printf(">> ");
        scanf("%d", &pilih);
        getchar();

        while(pilih<1 || pilih>i-1) {
            printf("Invalid Input!!!\n");
            printf("Please re-input\n\n");
            printf(">> ");
            scanf("%d", &pilih);
            getchar();
        }

        printf("\nRe-write Post :\n");
        printf(">> ");
        scanf("%[^\n]", &newpost);
        getchar();

        int val = validasiAlphaNumeric(newpost);

        while(val!=1) {
            clrScr();
            printf("Invalid Input!!!\n");
            printf("Input must be Alphanumeric only!\n");
            printf("Please re-input\n\n");
            printf(">> ");
            scanf("%[^\n]", &newpost);
            getchar();
            val = validasiAlphaNumeric(newpost);
        }

        printf("\nAre you sure you want to update your post?\n");
        printf("[1] Yes\n");
        printf("[2] No\n");
        printf(">> ");
        scanf("%d", &yesno);
        getchar();

        while(yesno<1 || yesno>2) {
            printf("Invalid Input!!!\n");
            printf("Please re-input\n\n");
            printf(">> ");
            scanf("%d", &yesno);
            getchar();
        }

        if(yesno==1) {
            updateData(newpost, pilih);
            printf("\nYour Post Has Been Updated!!!\n");
            printf("Press Enter to Continue...");
            getchar();
        }
        else {
            return;
        }
    }
}

int announceNotes (int value) {
    int pos=1;
    Notes *curr = head;
    while(pos!=value) {
        pos++;
        curr = curr->next;
    }
    curr->flag = 1;
    return 0;
}

void announce() {
    int i=1, pilih, yesno;
    Notes *curr = head;

    clrScr();

    if(curr==NULL) {
        printf("\nThere are no notes available!\n\n");
        printf("Press enter to back to menu...");
        getchar();
        return;
    }
    else {
        printf("\nWhich note do you want to announce?\n");
        while(curr) {
            if(curr->flag==0) {
                printf("[%d] %s\n", i, curr->note);
                i++;
            }
            curr = curr->next;
        }
        printf("-------------------------------------\n");
        printf("[%d] Back to menu\n", i);
        printf(">> ");
        scanf("%d", &pilih);
        getchar();

        while(pilih<1 || pilih>i) {
            printf("Invalid Input!!!\n");
            printf("Please re-input\n\n");
            printf(">> ");
            scanf("%d", &pilih);
            getchar();
        }

        if(pilih==i) {
            printf("\nPress Enter to go back to menu...");
            getchar();
            return;
        }

        printf("\nAre you sure you want to announce your post?\n");
        printf("[1] Yes\n");
        printf("[2] No\n");
        printf(">> ");
        scanf("%d", &yesno);
        getchar();

        while(yesno<1 || yesno>2) {
            printf("Invalid Input!!!\n");
            printf("Please re-input\n\n");
            printf(">> ");
            scanf("%d", &yesno);
            getchar();
        }

        if(yesno==1) {
            announceNotes(pilih);
            printf("\nYour Post Has Been Announce!!!\n");
            printf("Press Enter to Continue...");
            getchar();
        }
        else {
            return;
        }
    }
}

void Rbin() {
    int rec, pilih, i=1, yesno;

    binTrash *curr = h;
    clrScr();

    if(curr==NULL) {
        printf("=====================================\n");
        printf("|             TRASH BIN             |\n");
        printf("=====================================\n");
        printf("\nTrash Bin is empty!\n\n");
        printf("Press enter to back to menu...");
        getchar();
        return;
    }
    else {
        printf("=====================================\n");
        printf("|             TRASH BIN             |\n");
        printf("=====================================\n");

        while(curr) {
            int p = strlen(curr->bin);
            for(int i=0; i<p+6; i++) {
                printf("~");
            }
            printf("\n|  %s  |\n", curr->bin);
            for(int i=0; i<p+6; i++) {
                printf("~");
            }
            printf("\n");
            curr = curr->next;
        }

        printf("=====================================\n");
        printf("[1] Recover Note\n");
        printf("[2] Back\n");
        printf(">> ");
        scanf("%d", &rec);
        getchar();

        while(rec<1 || rec>2) {
            printf("Invalid Input!!!\n");
            printf("Please re-input\n\n");
            printf(">> ");
            scanf("%d", &rec);
            getchar();
        }

        if(rec==1) {
            clrScr();
            printf("Which note do you want to recover?\n");

            binTrash *dis = h;
            while(dis) {
                printf("[%d] %s\n", i, dis->bin);
                dis = dis->next;
                i++;
            }
            printf(">> ");
            scanf("%d", &pilih);
            getchar();

            while(pilih<1 || pilih>i-1) {
                printf("Invalid Input!!!\n");
                printf("Please re-input\n\n");
                printf(">> ");
                scanf("%d", &pilih);
                getchar();
            }

            printf("\nAre you sure you want to recover your post?\n");
            printf("[1] Yes\n");
            printf("[2] No\n");
            printf(">> ");
            scanf("%d", &yesno);
            getchar();

            while(yesno<1 || yesno>2) {
                printf("Invalid Input!!!\n");
                printf("Please re-input\n\n");
                printf(">> ");
                scanf("%d", &yesno);
                getchar();
            }

            if(yesno==1) {
                binTrash *now = h;
                for(int k=1; k<=i-1; k++) {
                    if(k==pilih) {
                        break;
                    }
                    now = now->next;
                }
                pushNote(now->bin);
                popBin(pilih);
                printf("\nYour Post Has Been Updated!!!\n");
                printf("Press Enter to Continue...");
                getchar();
            }
            else {
                return;
            }

        }
        else {
            return;
        }
    }
}

void seecomment(Notes *temp, int idx) {

    clrScr();
    printf("====================================\n");
    printf("|          NOTES DASHBOARD         |\n");
    printf("====================================\n");

    printf("\n");
    int p = strlen(temp->note); //printnya note yg udh dipilih

    for(int i=0; i<p+6; i++) {
        printf("~");
    }

    printf("\n|  %s  |\n", temp->note);

    for(int i=0; i<p+6; i++) {
        printf("~");
    }
    printf("\n");

    printf("[Comment: %d]\n", temp->com);

    temp->currlike = temp->hlike;
    while(temp->currlike) {
        printf("=> %s [Like : %d]\n", temp->currlike->comment, temp->currlike->like);
        temp->currlike = temp->currlike->next;
    }
}

void dashboardNotes(int idx) {
    int q=0;
    int likecom, yesno;
    int pilihLike;
    char comments[260];
    Notes *now = head;
    int pos=1;
    while(pos!=idx) {
        pos++;
        now = now->next;
    }

    while(q==0) {

        seecomment(now, idx);
        
        printf("\n====================================\n");
        printf("What do you want to do?\n");
        printf("[1] Comment\n");
        printf("[2] Like comment\n");
        printf("[3] Back\n");
        printf(">> ");
        scanf("%d", &likecom);
        getchar();

        while(likecom<1 || likecom>3) {
            printf("Invalid Input!!!\n");
            printf("Please re-input\n\n");
            printf(">> ");
            scanf("%d", &likecom);
            getchar();
        }
        
        if(likecom==1) {
            printf("\n\nWhat do you want to say?\n");
            printf(">> ");
            scanf("%[^\n]", &comments);
            getchar();

            int val = validasiAlphaNumeric(comments);

            while(val!=1) {
                clrScr();
                printf("Invalid Input!!!\n");
                printf("Input must be Alphanumeric only!\n");
                printf("Please re-input\n\n");
                printf("What do you want to say?\n");
                printf(">> ");
                scanf("%[^\n]", &comments);
                getchar();
                val = validasiAlphaNumeric(comments);
            } 

            printf("\nAre you sure you want to comment this post?\n");
            printf("[1] Yes\n");
            printf("[2] No\n");
            printf(">> ");
            scanf("%d", &yesno);
            getchar();

            while(yesno<1 || yesno>2) {
                printf("Invalid Input!!!\n");
                printf("Please re-input\n\n");
                printf(">> ");
                scanf("%d", &yesno);
                getchar();
            }

            if(yesno==1) {
                pushComment(now, comments);
                printf("\nYour Comment Has Been Posted!!!\n");
                printf("Press Enter to Continue...");
                getchar();

            //    seecomment(now, idx);
            }
            else {
                return;
            }
        } else if (likecom==2){
            if(now->com==0){
                printf("\n\nThere are no comments!\n");
                printf("\nPress enter to continue...");
                getchar();
            }
            else {
                int idxcom=1;
                printf("\n\nWhich comment do you want to like?\n");
                now->currlike = now->hlike;
                while(now->currlike) {
                    printf("[%d] %s\n", idxcom, now->currlike->comment);
                    now->currlike = now->currlike->next;
                    idxcom++;
                }

                printf("----------------------------------\n");
                printf("[%d] Back to menu\n", idxcom);
                printf(">> ");
                scanf("%d", &pilihLike);
                getchar();

                while(pilihLike<1 || pilihLike>idxcom) {
                    printf("Invalid Input!!!\n");
                    printf("Please re-input\n\n");
                    printf(">> ");
                    scanf("%d", &pilihLike);
                    getchar();
                }

                if(pilihLike==idxcom) {
                    printf("\nPress Enter to go back to menu...");
                    getchar();
                    return;
                }
                
                likeComment(now, pilihLike);
                printf("\nThe Comment Has Been Liked!!!\n");
                printf("Press Enter to Continue...");
                getchar();
            }
        }
        else {
            q=1;
            printf("\nPress enter to go back to Public Dashboard...");
            getchar();
            return;
        }
    }
}

void dashboard() {
    clrScr();
    int x=0;
    Notes *curr = head;

    if(curr==NULL) {
        printf("====================================\n");
        printf("|         PUBLIC DASHBOARD         |\n");
        printf("====================================\n");
        printf("\nPublic Dashboard is empty!\n\n");
        printf("Press enter to back to menu...");
        getchar();
        return;
    }
    else {
        while(x==0) {
            clrScr();
            Notes *dis = head;
            Notes *ann = head;
            int pilihDB, pilihNotes, i=1;

            printf("====================================\n");
            printf("|         PUBLIC DASHBOARD         |\n");
            printf("====================================\n");

            Notes *test = head;
            int A=0;
            while(test) {
                if(test->flag==1) {
                    A=1;
                    break;
                }
                test = test->next;
            }

            if(A==1) {
                printf("Announced Notes :\n");

                while(ann) {
                    if(ann->flag==1) {
                        int b = strlen(ann->note); //printnya note yg udh dipilih
                
                        for(int i=0; i<b+6; i++) {
                            printf("~");
                        }
                
                        printf("\n|  %s  |\n", ann->note);
                
                        for(int i=0; i<b+6; i++) {
                            printf("~");
                        }
                        printf("\n");

                        printf("[Comment: %d]\n", ann->com);
                        
                        ann->currlike = ann->hlike;
                        while(ann->currlike) {
                            printf("=> %s [Like : %d]\n", ann->currlike->comment, ann->currlike->like);
                            ann->currlike = ann->currlike->next;
                        }

                        printf("\n");
                    }
                    ann = ann->next;
                }
                printf("------------------------------------\n");
                
            }

            while(dis) {
            	// printf("\n");
		        int p = strlen(dis->note); //printnya note yg udh dipilih
		
		        for(int i=0; i<p+6; i++) {
		            printf("~");
		        }
		
		        printf("\n|  %s  |\n", dis->note);
		
		        for(int i=0; i<p+6; i++) {
		            printf("~");
		        }
		        printf("\n");
                printf("[Comment: %d]\n", dis->com);
		        
                dis->currlike = dis->hlike;
		        while(dis->currlike) {
		            printf("=> %s [Like : %d]\n", dis->currlike->comment, dis->currlike->like);
		            dis->currlike = dis->currlike->next;
		        }

                printf("\n");
                
                dis = dis->next;
            }

            printf("\n====================================\n");
            
            printf("What do you want to do next?\n");
            printf("[1] Check out specific notes\n");
            printf("[2] Back to Main Menu\n");
            printf(">> ");
            scanf("%d", &pilihDB);
            getchar();

            while(pilihDB<1 || pilihDB>2) {
                printf("Invalid Input!!!\n");
                printf("Please re-input\n\n");
                printf(">> ");
                scanf("%d", &pilihDB);
                getchar();
            }
            
            if(pilihDB==1){
                clrScr();
                printf("Which note do you want to check out?\n");
                Notes *curr = head;
                while(curr) {
                    printf("[%d] %s\n", i, curr->note);
                    curr = curr->next;
                    i++;
                }
                printf(">> ");
                scanf("%d", &pilihNotes);
                getchar();

                while(pilihNotes<1 || pilihNotes>i-1) {
                    printf("Invalid Input!!!\n");
                    printf("Please re-input\n\n");
                    printf(">> ");
                    scanf("%d", &pilihNotes);
                    getchar();
                }

                dashboardNotes(pilihNotes);
            }
            else {
                x=1;
                printf("\nPress Enter to Continue...");
                getchar();
                return;
            }
        }
    }
}

void menu5() {
    int choice, A=0;

    while(A==0) {
        clrScr();
        printf("==========================================\n");
        printf("| >> Add, Edit, Announce, Delete Note << |\n");
        printf("==========================================\n");
        printf("[1] Add Note\n");
        printf("[2] Edit Note\n");
        printf("[3] Announce Note\n");
        printf("[4] Delete Note\n");
        printf("[5] View Public Dashboard\n");
        printf("[6] View Trash Bin\n");
        printf("[7] Back to Main Menu\n");
        printf("==========================================\n");
        printf(">> ");
        scanf("%d", &choice);
        getchar();

        while(choice<1 || choice>7) {
            printf("Invalid Input!!!\n");
            printf("Please re-input\n\n");
            printf(">> ");
            scanf("%d", &choice);
            getchar();
        }

        if(choice==1) {
            addNote();
        }
        else if(choice==2) {
            editNote();
        }
        else if(choice==3) {
            announce();
        }
        else if(choice==4) {
            deleteNote();
        }
        else if(choice==5) {
            dashboard();
        }
        else if(choice==6) {
            Rbin();
        } 
        else if(choice==7){
            return;
        }
    }
}

//linked list untuk user yg bs direq (all user)
struct Node{
	char name[255];
	Node *prev, *next;
} *head1, *tail1; 

//createNode utk user yg bisa direquest
Node *createNode(const char *name){
	Node *newNode = (Node*)malloc(sizeof(Node)); 
	strcpy(newNode->name, name);
	newNode->next = NULL; 
	return newNode;
}

//pushtail ke user yg bisa di request list
void pushTail(const char *name){
	Node *temp = createNode(name);
	if(!head1){ 
    	head1 = tail1 = temp;
	}
	else{ 
		tail1->next = temp; 
	    tail1 = temp; 
    }
}

//linked list utk friend
struct Node2{
	char name[255];
	Node2 *prev, *next;
} *head2, *tail2; 

// createNode utk friendlist
Node2 *createNode2(const char *name){
	Node2 *newNode = (Node2*)malloc(sizeof(Node2)); 
	strcpy(newNode->name, name);
	newNode->next = NULL; 
	return newNode;
}

// pushTail ke friend list
void pushTail2(const char *name){
	Node2 *temp = createNode2(name);
	if(!head2){ 
    	head2 = tail2 = temp;
	}
	else{ 
		tail2->next = temp; 
	    tail2 = temp; 
    }
}

//linked list utk yg bs diacc
struct Node3{
	char name[255];
	Node3 *prev, *next;
} *head3, *tail3;

// createNode utk user yg diacc
Node3 *createNode3(const char *name){
	Node3 *newNode = (Node3*)malloc(sizeof(Node3)); 
	strcpy(newNode->name, name);
	newNode->next = NULL; 
	return newNode;
}

//push tail list yg bisa diacc
void pushTail3(const char *name){
	Node3 *temp = createNode3(name);
	if(!head3){ 
    	head3 = tail3 = temp;
	}
	else{ 
		tail3->next = temp; 
	    tail3 = temp; 
    }
}

void printReqList() 
{
    Node *curr = head1;
    banyakTeman = 1;

    while(curr)
    {
        printf("%d %s\n",banyakTeman, curr->name );
		banyakTeman++;
        curr = curr->next;
    }
}

void printFriendList(){
    Node2 *curr = head2;
    banyakTeman = 1;
    
    printf("[All Friends of %s]\n", usernameInput); //name of user login
    printf("No.   Username\n");
    while(curr){
        printf("%d     %s\n", banyakTeman, curr->name );
		banyakTeman++;
        curr = curr->next;
    }
}

struct req {
  char nama[25];
  req *next;
}*headRequest,*tailRequest;

req *newReq(char *nama){
  req *temp=(req*)malloc(sizeof(req));
  strcpy(temp->nama,nama);
  temp->next=NULL;

  return temp;
}

void sendRequest(char *username){
  req *newreq=newReq(username);
  
  if(!headRequest) { 
    headRequest = tailRequest = newreq; 
  } else { 
    newreq->next = headRequest; 
    headRequest = newreq; 
  }
}

void pushUser(){ // push user ke view inbox
    pushTail3("Susan");
    pushTail3("dini");
    pushTail3("Tini");
    pushTail3("sasa");
    pushTail3("beni");
}

void addFriend(userList **ref){
    printf("[All User]\n");
    viewUserList();
	printf("\n");
    printf("Which user do you want to add?\n");
    printf(">> ");
    char addUser[255];
    scanf("%[^\n]", addUser); getchar();

    userList *temp = *ref, *prev;
    if(temp != NULL && strcmpi(temp->username, addUser) == 0){ 
        printf("-- Your request has been sent to %s --\n", temp->username);
        sendRequest(temp->username);
        *ref = temp->next;
        free(temp);
        printf("Press enter to continue!\n");
        getchar();
        system("cls");
        return;
    } 
 
    while(temp != NULL && strcmpi(temp->username, addUser) != 0){ 
        prev = temp; 
        temp = temp->next; 
    } 

    if(temp == NULL){
    	printf("-- There is no %s here -- \n", addUser);
    	printf("Press enter to continue!\n");
        getchar();
        system("cls");
        return;
	}  

    printf("-- Your request has been sent to %s --\n", temp->username);
    sendRequest(temp->username);
    prev->next = temp->next; 
    free(temp);
    printf("Press enter to continue!\n");
    getchar();
    system("cls");
}

//remove user in friendlist
void removeFriend(Node2 **ref){
    printFriendList();
	printf("\n");
    printf("Which user do you want to remove?\n");
    printf(">> ");
    char remove[255];
    scanf("%[^\n]", remove); getchar();

    Node2 *temp = *ref, *prev;
    if(temp != NULL && strcmpi(temp->name, remove) == 0){ 
        printf("-- You are no longer friends with %s --\n", temp->name);
        printf("Press enter to continue!\n");
        getchar();
        system("cls");        
        *ref = temp->next;
        free(temp);
        return;
    } 
 
    while(temp != NULL && strcmpi(temp->name, remove) != 0){ 
        prev = temp; 
        temp = temp->next; 
    } 

    if(temp == NULL){
    	printf("-- You are not %s\'s friend\n", remove);
    	printf("Press enter to continue!\n");
        getchar();
        system("cls");
        return;
	} 
	
    printf("-- You are no longer friends with %s --\n", temp->name);
    printf("Press enter to continue!\n");
    getchar();
    system("cls");
        
    prev->next = temp->next; 
    free(temp);
}

//remove user from friend req list and push it to friend list
void viewInbox(Node3 **ref){
    char accepted[255];
    printf("[All Friend Requests of (name)]\n");
    printf("No.   Username\n");

	Node3 *curr = head3;
    int i = 1;                                      
	while(curr){ 
	    printf("%d     %s\n", i, curr->name);
	    curr = curr->next;
        i++;
	}
	printf("\n\n");
    printf("Which user do you want to be accepted?\n");
    printf(">> ");
    scanf("%[^\n]", accepted); getchar();

	char passToFL[255];
    Node3 *temp = *ref, *prev;
    if(temp != NULL && strcmpi(temp->name, accepted) == 0){
    	// push ke friend list
    	strcpy(passToFL, temp->name);
    	pushTail2(passToFL);
    	
    	// remove from view inbox
        printf("-- You accepted the request from %s --\n", temp->name);
        *ref = temp->next;
        free(temp);
        printf("Press enter to continue!\n");
        getchar();
        system("cls");
        return;
    } 
 
    while(temp != NULL && strcmpi(temp->name, accepted) != 0){ 
        prev = temp; 
        temp = temp->next; 
    } 

    if(temp == NULL){
    	printf("-- There is no request from %s\n", accepted);
    	printf("Press enter to continue!\n");
        getchar();
        system("cls");
        return;
	}  
    
	printf("-- You accepted the request from %s --\n", temp->name);
    printf("Press enter to continue!\n");
    getchar();
    system("cls");
        
    pushTail2(temp->name);
    prev->next = temp->next; 
    free(temp);
}


void printReq(){ // menu 4
  req *curr=headRequest;

    printf("\n\n--------- YOUR PENDING LIST --------\n\n");
    printf("-----------------------------------------\n\n");
    printf("[All Your Sent Friend Requests That Are Still Pending]\n");

    int i = 1;
  while (curr){
    printf("%d  %s\n", i, curr->nama);
    curr=curr->next;
    i++;
  }
  printf("Press enter to continue!\n");
  getchar();
  system("cls");
}
// ends here

void user_page(){ 
    int x=0;
    while (x==0){
        system("cls");
        printf("Oo=====================================oO\n");
        printf("Welcome, %s!\n", usernameInput);
        printf("Oo=====================================oO\n");
        time_t current_date_and_time;
        time(&current_date_and_time);
        printf("Logged in: %s\n", ctime(&current_date_and_time));
        printf("-----------------------------------------\n");
        printFriendList();
        

        printf("\n-------------------------------------------\n");
        printf("                  >>Menu<<                 \n");
        printf("-------------------------------------------\n");
        printf("[1] Add Friend\n");
        printf("[2] Remove Friend\n");
        printf("[3] View Inbox\n");
        printf("[4] View Sent Request\n");
        printf("[5] Add, Edit, Announce, Delete Note\n");
        printf("[6] Log out\n");
        printf("-----------------------------------------\n");
        printf(">> ");
        int numberInput;
        scanf("%d", &numberInput);
        getchar();
        while(numberInput<1 || numberInput>6){
            printf("Invalid Input!!!\n");
            printf("Please re-input\n\n");
            printf(">> ");
            scanf("%d", &numberInput);
            getchar();
        }
        if(numberInput==1){
            addFriend(&headList);
         }
        else if(numberInput==2){
            removeFriend(&head2);
        }
        else if(numberInput==3){
            viewInbox(&head3);
        }
        else if(numberInput==4){
            printReq();
        }
        else if(numberInput==5){
            menu5();
        }
        else if(numberInput==6){
            x=1;
            return;
        }
    }
}

int main()
{
    int choice = -1;
    char address[35];
    viewawal();
    do
    {
        system("cls");
        displayMainMenu();
        scanf("%d", &choice);
        getchar();
        switch (choice)
        {
        case 1:
            regis();
            break;
        case 2:
            if (login(address))
            {
                puts("\n\n--- Login Successfull ---");
                puts("Press enter to continue");
                getchar();
                system("cls");
                pushUser();
                user_page();
            }
            else
            {
                puts("\n\n--- Login Failed ---");
                puts("Press enter to go back to Main Page...");
                getchar();
            }
            break;
        default:
            break;
        }
    } while (choice != 3);

    return 0;
}
