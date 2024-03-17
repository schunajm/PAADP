## ----include = FALSE----------------------------------------------------------
knitr::opts_chunk$set(
  collapse = TRUE,
  comment = "#>"
)

## ----setup, warning=FALSE, message=FALSE--------------------------------------
library(activAnalyzer)
library(magrittr)
library(ggplot2)
library(patchwork)
library(dplyr)

## -----------------------------------------------------------------------------
file <- system.file("extdata", "acc.agd", package = "activAnalyzer")

## ----warning=FALSE, message=FALSE---------------------------------------------
mydata <- prepare_dataset(data = file)

## ----message = FALSE----------------------------------------------------------
mydata_with_wear_marks <- 
  mydata %>%
  mark_wear_time(
    to_epoch = 60,
    cts = "vm",
    frame = 90, 
    allowanceFrame = 2, 
    streamFrame = 30
    )

## ----include=FALSE------------------------------------------------------------
height_factor <- nlevels(as.factor(mydata_with_wear_marks$date)) * 0.80

## ----fig.height = height_factor, fig.width=7, fig.align="center"--------------
plot_data(data = mydata_with_wear_marks, metric = "vm")

## ----fig.height = height_factor, fig.width=7, fig.align="center"--------------
plot_data(
  data = mydata_with_wear_marks, 
  metric = "vm",
  zoom_from = "16:00:00",
  zoom_to = "18:00:00"
  )

## ----warning = FALSE, message = FALSE-----------------------------------------
mydata_with_intensity_marks <- 
  mark_intensity(
     data = mydata_with_wear_marks, 
     col_axis = "vm", 
     equation = "Sasaki et al. (2011) [Adults]",
     sed_cutpoint = 200, 
     mpa_cutpoint = 2690, 
     vpa_cutpoint = 6167, 
     age = 32,
     weight = 67,
     sex = "male"
    )

## ----fig.height = height_factor, fig.width=7, fig.align="center"--------------
plot_data_with_intensity(
  mydata_with_intensity_marks, 
  metric = "vm",
  valid_wear_time_start = "00:00:00",
  valid_wear_time_end = "23:59:59"
  )

## ----fig.height = height_factor, fig.width=7, fig.align="center"--------------
plot_data_with_intensity(
  mydata_with_intensity_marks, 
  metric = "vm",
  valid_wear_time_start = "07:00:00",
  valid_wear_time_end = "22:00:00"
  )

## ----fig.height = height_factor, fig.width=7, fig.align="center"--------------
plot_data_with_intensity(
  mydata_with_intensity_marks, 
  metric = "vm",
  zoom_from = "13:00:00",
  zoom_to = "16:30:00"
  )

## ----message = FALSE----------------------------------------------------------
results_by_day <-
  mydata_with_intensity_marks %>%
  recap_by_day(
    age = 32, 
    weight = 67, 
    sex = "male",
    valid_wear_time_start = "07:00:00",
    valid_wear_time_end = "22:00:00",
    start_first_bin = 0,
    start_last_bin = 10000,
    bin_width = 500
    )

## ----eval---------------------------------------------------------------------
mean_results <-
  results_by_day$df_all_metrics  %>%
  average_results(minimum_wear_time = 10, fun = "mean")

## -----------------------------------------------------------------------------
median_results <-
  results_by_day$df_all_metrics  %>%
  average_results(minimum_wear_time = 10, fun = "median")

## -----------------------------------------------------------------------------
results_by_day$df_all_metrics %>% 
  dplyr::select(date:total_steps) %>%
  reactable::reactable(striped = TRUE, defaultColDef = reactable::colDef(align = "center", minWidth = 180))

## ----fig.height=10, fig.width = 17, warning=FALSE, message=FALSE--------------
create_fig_res_by_day(
  results_by_day$df_all_metrics, 
  minimum_wear_time_for_analysis = 10, 
  start_day_analysis = "00:00:00", 
  end_day_analysis = "23:59:00", 
  metrics = "volume",
  epoch_label = "60s"
  ) + theme(plot.margin = margin(1, 1, 1, 1, "cm"))

## -----------------------------------------------------------------------------
create_flextable_summary(
  results_summary_means = mean_results, 
  results_summary_medians = median_results, 
  metrics = "volume",
  epoch_label = "60s"
  )

## ----fig.height=9, fig.width = 17, warning=FALSE, message=FALSE---------------
# PAL
g_pal <- create_fig_pal(score = mean_results[["pal"]], "en") + theme(plot.margin = margin(2, 1, 0.5, 1, "cm"))
  
# Steps
g_steps <- create_fig_steps(score = mean_results[["total_steps"]], "en") + theme(plot.margin = margin(0, 1, 0.5, 1, "cm"))

# MVPA
g_mvpa <- create_fig_mvpa(score = mean_results[["minutes_MVPA"]], "en") + theme(plot.margin = margin(0, 1, 0, 1, "cm"))

# SED
g_sed <- create_fig_sed(score = mean_results[["minutes_SED"]], "en") + theme(plot.margin = margin(0, 1, 0, 1, "cm"))

# MVPA/SED ratio
g_ratio <- create_fig_ratio_mvpa_sed(score = mean_results[["ratio_mvpa_sed"]], "en") + theme(plot.margin = margin(0, 1, 1, 1, "cm"))

# Whole figure
g_pal / g_steps / (g_mvpa | g_sed | g_ratio) + 
    plot_layout(heights = c(0.8, 0.7, 1.5)) & theme(legend.justification = "center")

## -----------------------------------------------------------------------------
results_by_day$df_all_metrics %>% 
  dplyr::select(date, max_steps_60min:peak_steps_1min) %>%
  reactable::reactable(striped = TRUE, defaultColDef = reactable::colDef(align = "center", minWidth = 180))

## ----fig.height=7, fig.width = 17, warning=FALSE, message=FALSE---------------
create_fig_res_by_day(
  results_by_day$df_all_metrics, 
  minimum_wear_time_for_analysis = 10, 
  start_day_analysis = "00:00:00", 
  end_day_analysis = "23:59:00", 
  metrics = "step_acc",
  epoch_label = "60s"
  ) + theme(plot.margin = margin(1, 1, 1, 1, "cm"))

## -----------------------------------------------------------------------------
create_flextable_summary(
  results_summary_means = mean_results, 
  results_summary_medians = median_results,
  metrics = "step_acc",
  epoch_label = "60s"
  )

## ----fig.width = 15, fig.height = 10------------------------------------------
  results_by_day$p_band

## ----fig.width = 15, fig.height = 10, message = FALSE-------------------------
  results_by_day$p_log

## -----------------------------------------------------------------------------
results_by_day$df_all_metrics %>% 
  dplyr::select(date, ig:M5) %>%
  reactable::reactable(striped = TRUE, defaultColDef = reactable::colDef(align = "center", minWidth = 180))

## ----fig.height=7, fig.width = 17, warning=FALSE, message=FALSE---------------
create_fig_res_by_day(
  results_by_day$df_all_metrics, 
  minimum_wear_time_for_analysis = 10, 
  start_day_analysis = "00:00:00", 
  end_day_analysis = "23:59:00", 
  metrics = "int_distri",
  epoch_label = "60s"
  ) + theme(plot.margin = margin(1, 1, 1, 1, "cm"))

## -----------------------------------------------------------------------------
create_flextable_summary(
  results_summary_means = mean_results, 
  results_summary_medians = median_results,
  metrics = "int_distri",
  epoch_label = "60s"
  )

## ----fig.align = "center", out.width='50%', out.height='50%', fig.width=8, fig.height=8----
create_fig_mx_summary(
data = mean_results,
labels = NULL,
mpa_cutpoint = 2690, 
vpa_cutpoint = 6167
)

## -----------------------------------------------------------------------------
accum_metrics_sed <- 
  compute_accumulation_metrics(
    data = mydata_with_intensity_marks, 
    behaviour = "sed",
    dates = c("2021-04-07", "2021-04-08", "2021-04-09", "2021-04-10", "2021-04-11")
    )

## ----fig.height = height_factor/0.75*0.85, fig.width=7, fig.align="center"----
accum_metrics_sed$p_breaks

## ----out.width='100%', out.height='60%', fig.height=11, fig.width=11, fig.align="center"----
p1 <- accum_metrics_sed$p_alpha  + guides(color = "none", fill = "none")
p2 <- accum_metrics_sed$p_MBD    + guides(color = "none", fill = "none")
p3 <- accum_metrics_sed$p_UBD
p4 <- accum_metrics_sed$p_gini

(p1 | p2) / (p3 | p4) + plot_layout(guides = "collect") & theme(legend.position = 'bottom') 

## -----------------------------------------------------------------------------
accum_metrics_pa <- 
  compute_accumulation_metrics(
    mydata_with_intensity_marks, 
    behaviour = "pa",
    dates = c("2021-04-07", "2021-04-08", "2021-04-09", "2021-04-10", "2021-04-11")
    )

## ----fig.height = height_factor/0.75*0.85, fig.width=7, fig.align="center"----
accum_metrics_pa$p_breaks

## ----out.width='100%', out.height='60%', fig.height=11, fig.width=11, fig.align="center"----
p1 <- accum_metrics_pa$p_alpha  + guides(color = "none", fill = "none")
p2 <- accum_metrics_pa$p_MBD    + guides(color = "none", fill = "none")
p3 <- accum_metrics_pa$p_UBD
p4 <- accum_metrics_pa$p_gini

(p1 | p2) / (p3 | p4) + plot_layout(guides = "collect") & theme(legend.position = 'bottom') 

