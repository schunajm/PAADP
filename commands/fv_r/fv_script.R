
###Initial Code####

###Make Sure to Grab the R-Portable LibPath Only###
wdir <- getwd()
libfin <- paste0(substr(wdir,1,nchar(wdir) - 3),"library")
.libPaths(libfin)

###File Viewer Function####
procfileview <- function(){
  tryCatch({######Grab the Correct Directories for Accessing Commands#####
  wdir <- getwd()
  outpath <- paste0(substr(wdir,1,nchar(wdir) - 13),"commands/fv/fv_output.txt")
  wripath <- paste0(substr(wdir,1,nchar(wdir) - 13),"commands/fv_written/fvwri_output.txt")
  fvap <- read.table(outpath, header = F, sep="\t")
  
  ####Grab the Error Log Path and Create Dump File - Populated As Needed###
  errpath <- paste0(substr(wdir,1,nchar(wdir) - 13),"errors/fv/errors.txt")
  
  ###Clear out the Error File If There######
  file.remove(dir(paste0(substr(wdir,1,nchar(wdir) - 13),"errors/fv/"),
                  pattern = "*.txt", full.names=T))
  
  ###Clear out the Previous File Viewer If There######
  file.remove(dir(paste0(substr(wdir,1,nchar(wdir) - 13),"commands/fv_written/"),
                  pattern = "*.txt", full.names=T))
  
  #####Initialize File Viewer Inputs########
  filen <- NA; start1 <- NA; stop1 <- NA
  
  ####Grab the File Viewer Inputs#####
  try(filen <- substr(fvap[3,1], 20, nchar(fvap[3,1])))
  try(start1 <- as.numeric(substr(fvap[1,1], 15, nchar(fvap[1,1]))))
  try(stop1 <- as.numeric(substr(fvap[2,1], 13, nchar(fvap[2,1]))))
  
  ####Read-In the File####
  floutput <- readr::read_lines(filen, skip = (start1 - 1), n_max = ((stop1 - start1)+1))
  
  ###Write the Data to File####
  readr::write_lines(floutput, wripath)},
  error = function(err.msg){
    write(toString(err.msg), errpath, append=TRUE)
  })
}

procfileview()


