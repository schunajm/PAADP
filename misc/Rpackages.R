###Make Sure to Grab the R-Portable LibPath Only###
wdir <- getwd()
libfin <- paste0(substr(wdir,1,nchar(wdir) - 3),"library")
.libPaths(libfin)

install.packages(c("data.table","GGIR","GGIRread","GENEAread","gsignal","read.gt3x",
                   "Hmisc","MASS","matrixStats","Rcpp","stringr","writexl","MIMSunit",
                   "accelerometry","PhysicalActivity","acc","activAnalyzer"),
                 dependencies=T)
