#include "control.h"

int control_init( data_control * dcontrol ) {

  if( pthread_mutex_init(&(dcontrol->mutex),NULL) )
    return 1;
  if( pthread_cond_init(&(dcontrol->cond),NULL) )
    return 1;
  dcontrol->active = 0;
  return 0;
}

int control_destroy( data_control * dcontrol ) {
  
  if( pthread_mutex_destroy(&(dcontrol->mutex)) )
    return 1;
  if( pthread_cond_destroy(&(dcontrol->cond)) )
    return 1;
  dcontrol->active = 0;
}

int control_activate( data_control * dcontrol ) {
  
  if( pthread_mutex_lock(&(dcontrol->mutex)) )
    return 0;
  dcontrol->active = 1;
  pthread_mutex_unlock(&(dcontrol->mutex));
  pthread_cond_broadcast(&(dcontrol->cond));
  return 1;
}

int control_deactivate( data_control *dcontrol ) {
  
  if( pthread_mutex_lock(&(dcontrol->mutex)) )
    return 0;
  dcontrol->active = 0;
  pthread_mutex_unlock(&(dcontrol->mutex));
  pthread_cond_broadcast(&(dcontrol->cond));
  return 1;
}
