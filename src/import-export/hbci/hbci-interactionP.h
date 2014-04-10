/* hbci-interactorP.h -- private header for the functionality offerd by the 
   method in hbci-interaction.h.
   Copyright 2002 by Christian Stimming <stimming@tuhh.de> */

/***************************************************************************
 *                                                                         *
 *   This library is free software; you can redistribute it and/or         *
 *   modify it under the terms of the GNU Lesser General Public            *
 *   License as published by the Free Software Foundation; either          *
 *   version 2.1 of the License, or (at your option) any later version.    *
 *                                                                         *
 *   This library is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU     *
 *   Lesser General Public License for more details.                       *
 *                                                                         *
 *   You should have received a copy of the GNU Lesser General Public      *
 *   License along with this library; if not, write to the Free Software   *
 *   Foundation, Inc., 59 Temple Place, Suite 330, Boston,                 *
 *   MA  02111-1307  USA                                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef HBCI_INTERACTIONP_H
#define HBCI_INTERACTIONP_H

#include <openhbci/interactor.h>
#include <openhbci/progressmonitor.h>
#include <gnome.h>


typedef enum {
  INIT,
  RUNNING,
  FINISHED,
  ABORTED,
  CLOSING
} PMon_state;

struct _inter_data 
{
  GtkWidget *parent;
  GtkWidget *dialog;

  /* Progress bars */
  GtkWidget *job_entry;
  GtkWidget *action_entry;
  GtkWidget *action_progress;

  /* Log window */
  GtkWidget *log_text;

  /* Buttons */
  GtkWidget *abort_button;
  GtkWidget *close_button;
  GtkWidget *close_checkbutton;

  const char *format_pin_user_bank;
  const char *format_pin_min_char;
  
  /* Flags to keep track on whether an HBCI action is running or
     not. */
  gboolean keepAlive;
  PMon_state state;

  /* Counters for progress bar */
  int jobs;
  int current_job;
  int actions;
  int current_act;

  /* Flag on Whether the PIN should be cached. */
  gboolean cache_pin;
  /* The cached PIN and the HBCI_User it's cached for. */
  char *pw;
  const HBCI_User *user;
};

void delete_GNCInteractor (GNCInteractor *data);

HBCI_ProgressMonitor *
gnc_hbci_new_pmonitor(GNCInteractor *data);

HBCI_Interactor *
gnc_hbci_new_interactor(GNCInteractor *data);

void add_log_text (GNCInteractor *data, const char *msg);



#endif