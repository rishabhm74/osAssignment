#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
#include<pthread.h>



pthread_mutex_t mylock;
int things_table[4][3] = {0};//last row signifies wheteher the student has finished the assignment or not 0 -> not finished 1 -> finished

void *student1(){
    pthread_mutex_lock(&mylock);
    printf("\nStudent1 took 2(Paper) and 3(Question Paper).\n");
    //as by default he had pen
    things_table[3][0] = 1;
    printf("Student1 is finished with the assisgnment.\n");
    pthread_mutex_unlock(&mylock);
}

void *student2(){
    pthread_mutex_lock(&mylock);
    printf("\nStudent2 took 1(Pen) and 3(Question Paper).\n");
    //as by default he had paper
    things_table[3][1] = 1;
    printf("Student2 is finished with the assisgnment.\n");
    pthread_mutex_unlock(&mylock);
}

void *student3(){
    pthread_mutex_lock(&mylock);
    printf("\nStudent3 took 1(Pen) and 2(Paper).\n");
    //as by default he had pen
    things_table[3][2] = 1;
    printf("Student3 is finished with the assisgnment.\n");
    pthread_mutex_unlock(&mylock);
}

int choice1, choice2;
//considering user to be teacher and he keeps resources on tablw
void *teacher()
{
	pthread_mutex_lock(&mylock);
	printf("\nResource 1 to be kept on table: ");
	scanf("%d",&choice1);  
	printf("\nResource 2 to be kept on table: ");
	scanf("%d",&choice2);
	pthread_mutex_unlock(&mylock);
}


int main(){
    pthread_mutex_init(&mylock, NULL);
    
    pthread_t student_thread;
    pthread_t teacher_thread;
    /*
    1 -> pen
    2 -> paper
    3 -> queston_paper
    */
    things_table[0][0] = 1; //student1 has pen
    things_table[1][1] = 2; //student2 has paper
    things_table[2][2] = 3; //student3 has question_paper
    
    printf("\t\t\t\t\t  --by Rishabh Mishra,K18KR,11811114\n");
    //printf("\t\t\t\t\t\t\t\t\n");
    printf("\n\t\t     Allocations(what each number means)\n\n");
    printf("\t 1 --> Pen\t\t2 --> Paper\t\t3 --> Question Paper\n");
/*
    for(int i=0;i<4;i++){
        for(int j = 0; j<3;j++){
            printf("\t%d\t",things_table[i][j]);
        }
        printf("\n");
    }
*/
    while(1 > 0){
        //check if stuent has already done the assignment or not
        if(things_table[3][0] && things_table[3][1] && things_table[3][2]){
            break;
            //if done come out of the loop 
            //as they dont need any resources
        }
        
        pthread_create(&teacher_thread, NULL, teacher, NULL);
        pthread_join(teacher_thread, NULL);

        if(((choice1 == 2 && choice2 == 3) ||(choice1 == 3 && choice2 == 2)) && things_table[3][0] == 0){
            pthread_create(&student_thread, NULL, student1, NULL);
            pthread_join(student_thread, NULL);
        }
        else if(((choice1 == 1 && choice2 == 3) ||(choice1 == 3 && choice2 == 1)) && things_table[3][1] == 0){
            pthread_create(&student_thread, NULL, student2, NULL);
            pthread_join(student_thread, NULL);
        }
        else if(((choice1 == 1 && choice2 == 2) ||(choice1 == 2 && choice2 == 1)) && things_table[3][2] == 0){
            pthread_create(&student_thread, NULL, student3, NULL);
            pthread_join(student_thread, NULL);
        }
        else{
            printf("\nEither all the students are finished with their assisgnments or you have given wrong inputs!\n");
        }
    }

    printf("\n");
    for(int i =0;i<6;i++){
        printf("Exiting from the program...\n");
    }
}
