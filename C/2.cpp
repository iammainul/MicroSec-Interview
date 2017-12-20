#include <iostream>
#include <cstdlib>
#include <pthread.h>
#include <unistd.h>

using namespace std;

void *wait(void *t) {
   int i;
   long tid;

   tid = (long)t;

   sleep(1);
   cout << "Sleeping in thread " << endl;
   cout << "Thread with id : " << tid << "  exiting " << endl;
   pthread_exit(NULL);
}

int main () {
   int r;
   int i,n;
   pthread_t threads[100];
   pthread_attr_t attr;
   void *status;

   cin >> n;

   // Initialize and set thread joinable
   pthread_attr_init(&attr);
   pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

   for( i = 0; i < n; i++ ) {
      cout << "Main : creating thread, " << i << endl;
      r = pthread_create(&threads[i], NULL, wait, (void *)i );
      
      if (r) {
         cout << "Error:unable to create thread," << r << endl;
         exit(-1);
      }
   }

   // free attribute and wait for the other threads
   pthread_attr_destroy(&attr);
   for( i = 0; i < n; i++ ) {
      r = pthread_join(threads[i], &status);
      if (r) {
         cout << "Error:unable to join," << r << endl;
         exit(-1);
      }
      
      cout << "Main: completed thread id :" << i ;
      cout << "  exiting with status :" << status << endl;
   }

   cout << "Main: Thread exiting." << endl;
   pthread_exit(NULL);
}
