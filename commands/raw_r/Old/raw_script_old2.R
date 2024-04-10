
###Initial Code####

###Make Sure to Grab the R-Portable LibPath Only###
wdir <- getwd()
libfin <- paste0(substr(wdir,1,nchar(wdir) - 3),"library")
.libPaths(libfin)

###Custom Functions for Global Processing####
round2 <- function(x, n) {
  posneg = sign(x)
  z = abs(x)*10^n
  z = z + 0.5
  z = trunc(z)
  z = z/10^n
  z*posneg
}

######Grab the Correct Directories for Accessing Commands#####
wdir <- getwd()
outpath <- paste0(substr(wdir,1,nchar(wdir) - 13),"commands/raw/raw_output.txt")
outpath2 <- paste0(substr(wdir,1,nchar(wdir) - 13),"commands/raw/raw_output2.csv")

test <- read.table(outpath, header = F, sep="\t")
write.table(test, outpath2, sep=",", col.names=T, row.names=F, append=F, quote=F)

####Progress Bar####
n_iter <- 50 # Number of iterations

pb <- winProgressBar(title = "PADDP Raw Data Processing", # Window title
                     label = "Percentage completed", # Window label
                     min = 0,      # Minimum value of the bar
                     max = n_iter, # Maximum value of the bar
                     initial = 0,  # Initial value of the bar
                     width = 300L) # Width of the window 

for(i in 1:n_iter) {
  
  #---------------------
  # Code to be executed
  #---------------------
  
  Sys.sleep(0.1) # Remove this line and add your code
  
  #---------------------
  
  pctg <- paste(round(i/n_iter *100, 0), "% completed")
  setWinProgressBar(pb, i, label = pctg) # The label will override the label set on the
  # winProgressBar function
}

close(pb) # Close the connection