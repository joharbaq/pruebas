#include "planificador.h"

/* Lista interna de tareas a ejecutarse */
struct Task* _scheduled_tasks[MAX_TASKS];

tTime TimeNow_ms()
{

	struct timespec tms;

	if (clock_gettime(CLOCK_MONOTONIC,&tms)) {
		return -1;
	}

	tTime now = (tms.tv_sec * 1000) + tms.tv_nsec/1000000;

	/* redondear hacia arriba */
	if(tms.tv_nsec % 1000000 > 500000)
		++now;

	return now;
}

tTime TimePassed_ms(tTime since)
{
	tTime now = TimeNow_ms();

	return now - since;
}

bool SchedulerAddTask(struct Task* t)
{
	/* TODO: Agregar t a la lista interna de tareas */
	for(int i=0;i<MAX_TASKS;i++)
		if(_scheduled_tasks[i] == NULL){
			_scheduled_tasks[i] = t;
			return true;
		}
	return false;
}

void SchedulerRun()
{
	/* TODO: Recorrer la lista interna de tareas y ejecutar una tarea habilitada con runNextAt expirado */
	struct Task *t;

	for(int i=0;i<MAX_TASKS;i++){
		t= _scheduled_tasks[i];
		if((t != NULL) && (t->enabled) && (TimeNow()>=t->runNextAt)){
			t->callback(t);
			if(t->timeBetweenRuns  != 0){
				TaskResetPeriodic(t);
			}else{
				free(t);
				_scheduled_tasks[i] = NULL;
				
		}		
	}
}
}

struct Task *TaskNew(tTime now, tTime timeFromNow, tTime timeBetweenRuns, TaskCallback callback)
{
	/* TODO: Crear una tarea en el heap, incializar la tarea */
	struct Task *t= (struct Task *) calloc(1,sizeof(struct Task));
	t->runNextAt = timeFromNow + now;
	t->timeBetweenRuns = timeBetweenRuns;
	t->callback = callback;
	t->enabled = false;

	return t;
}

void TaskResetPeriodic(struct Task *t)
{
	t->runNextAt = TimeNow_ms() + t->timeBetweenRuns;
}

void TaskSetNextTime(struct Task *t, tTime timeFromNow)
{
	t->runNextAt = TimeNow_ms() + timeFromNow;
}

void TaskDisable(struct Task* t)
{
	t->enabled = false;
}

void TaskEnable(struct Task* t)
{
	t->enabled = true;
}