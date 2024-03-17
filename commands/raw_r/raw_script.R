
###Initial Code####

###Make Sure to Grab the R-Portable LibPath Only###
wdir <- getwd()
libfin <- paste0(substr(wdir,1,nchar(wdir) - 3),"library")
.libPaths(libfin)

######Grab the Correct Directories for Accessing Commands#####
procrawdata <- function(){
  ######Grab the Correct Directories for Accessing Commands#####
  ###setwd("H:/PAADP/R/R-4.3.3/bin")
  wdir <- getwd()
  outpath <- paste0(substr(wdir,1,nchar(wdir) - 13),"commands/raw/raw_output.txt")
  rawp <- read.table(outpath, header = F, sep="\t")

  ####Grab the Error Log Path and Create Dump File - Populated As Needed###
  errpath <- paste0(substr(wdir,1,nchar(wdir) - 13),"errors/raw/errors.txt")

  ###Clear out the Error File If There######
  file.remove(dir(paste0(substr(wdir,1,nchar(wdir) - 13),"errors/raw/"),
                  pattern = "*.txt", full.names=T))

  #####Initialize Raw Data Processing Inputs########
  filen <- NA;
  pat1 <- NA; pat2 <- NA; pat2b <- NA; pat2c <- NA; pat2d <- NA; pat2e <- NA; pat2f <- NA; pat2g <- NA
  startloc <- NA; stoploc <- NA; stoploc1 <- NA; stoploc2 <- NA; stoploc3 <- NA; stoploc4 <- NA; stoploc5 <- NA; stoploc6 <- NA; stoploc7 <- NA;
  fnum <- NA; files <- NA; filenames <- NA
  samprate <- NA; startrow <- NA; xcol <- NA; ycol <- NA; zcol <- NA; vmcol <- NA; tstamp <- NA;
  resamp <- NA; resampfz <- NA; calibration <- NA; vmonly <- NA;
  tcol <- NA; tform <- NA; drow <- NA; dform <- NA; sdate <- NA
  trow <- NA; tform2 <- NA; stime <- NA; vars <- NA; varslist <- NA; rethead <- NA;
  multithread <- NA; startunits <- NA; endunits <- NA; extenin <- NA
  epoch <- NA; outform <- NA; outdir <- NA; varstf <- NA; varsind <- NA

  #####Identify the System########
  #####Only Really Works for Windows Currently###
  sysin <- paste(Sys.info()[1])

  if(sysin == "Windows"){
    try(filen <- gsub("\\\\", "/", substr(rawp[7,1], 18, nchar(rawp[7,1]))))
    try(pat1 <- "([:upper:][:])"); try(pat2 <- "([.][g][t][3][x])"); try(pat2b <- "([.][b][i][n])"); try(pat2c <- "([.][c][w][a])")
    try(pat2d <- "([.][t][x][t])"); try(pat2e <- "([.][d][a][t])"); try(pat2f <- "([.][t][a][b])"); try(pat2g <- "([.][c][s][v])")
    try(startloc <- data.frame(stringr::str_locate_all(filen, pat1))); try(stoploc1 <- data.frame(stringr::str_locate_all(filen, pat2)))
    try(stoploc2 <- data.frame(stringr::str_locate_all(filen, pat2b))); try(stoploc3 <- data.frame(stringr::str_locate_all(filen, pat2c)))
    try(stoploc4 <- data.frame(stringr::str_locate_all(filen, pat2d))); try(stoploc5 <- data.frame(stringr::str_locate_all(filen, pat2e)))
    try(stoploc6 <- data.frame(stringr::str_locate_all(filen, pat2f))); try(stoploc7 <- data.frame(stringr::str_locate_all(filen, pat2g)))
    try(stoploc <- rbind(stoploc1,stoploc2,stoploc3,stoploc4,stoploc5,stoploc6,stoploc7))
    try(stoploc <- rbind(stoploc1,stoploc2,stoploc3,stoploc4,stoploc5,stoploc6,stoploc7))
    try(fnum <- 1:nrow(startloc)); try(filenames <- c())
    try(for(i in fnum){
      files[i] <- substr(filen, startloc$start[i], stoploc$end[i])
      filenames[i] <- files[i]
    })
  } else if (sysin == "Linux"){
    NULL
  } else {
    NULL
  }

  #####Collect Data from the GUI#####
  try(samprate <- as.numeric(substr(rawp[10,1], 14, nchar(rawp[10,1])))); try(startrow <- as.numeric(substr(rawp[12,1], 17, nchar(rawp[12,1]))))
  try(xcol <- as.numeric(substr(rawp[13,1], 16, nchar(rawp[13,1])))); try(ycol <- as.numeric(substr(rawp[14,1], 16, nchar(rawp[14,1]))))
  try(zcol <- as.numeric(substr(rawp[15,1], 16, nchar(rawp[15,1])))); try(vmcol <- as.numeric(substr(rawp[16,1], 12, nchar(rawp[16,1]))))
  try(resamp <- substr(rawp[20,1], 11, nchar(rawp[20,1]))); try(resampfz <- as.numeric(substr(rawp[11,1], 16, nchar(rawp[11,1]))))
  try(calibration <- substr(rawp[21,1], 14, nchar(rawp[21,1]))); try(vmonly <- substr(rawp[22,1], 15, nchar(rawp[22,1])))
  try(startunits <- substr(rawp[1,1], 14, nchar(rawp[1,1])))
  try(tstamp <- ifelse(substr(rawp[42,1], 12, nchar(rawp[42,1])) == "True", "Yes1",
                       ifelse(substr(rawp[43,1], 12, nchar(rawp[43,1])) == "True", "Yes2",
                              ifelse(substr(rawp[44,1], 13, nchar(rawp[44,1])) == "True", "Yes3", "No"))))
  try(tcol <- as.numeric(substr(rawp[17,1], 19, nchar(rawp[17,1])))); try(tform <- substr(rawp[2,1], 17, nchar(rawp[2,1])))
  try(drow <- as.numeric(substr(rawp[18,1], 11, nchar(rawp[18,1])))); try(dform <- substr(rawp[3,1], 12, nchar(rawp[3,1])))
  try(trow <- as.numeric(substr(rawp[19,1], 11, nchar(rawp[19,1])))); try(tform2 <- substr(rawp[4,1], 12, nchar(rawp[4,1])));
  try(sdate <- substr(rawp[8,1], 13, nchar(rawp[8,1]))); try(stime <- substr(rawp[9,1], 13, nchar(rawp[9,1])))
        ####Get the Variables To Compute####
        try(varslist <- c("SVM","SVMgs","ENMO","LFENMO","BFEN","HFEN","HFENp","MAD","MIMS",
                      "COUNTS","COUNTS_LF","SED_SPHERE","WAISTEPS1","WAISTEPS2","WRISTEPS"))
        try(varstf <- c(substr(rawp[23,1], 6, nchar(rawp[23,1])), substr(rawp[24,1], 8, nchar(rawp[24,1])),
                      substr(rawp[25,1], 7, nchar(rawp[25,1])), substr(rawp[26,1], 9, nchar(rawp[26,1])),
                      substr(rawp[27,1], 7, nchar(rawp[27,1])), substr(rawp[28,1], 7, nchar(rawp[28,1])),
                      substr(rawp[29,1], 8, nchar(rawp[29,1])), substr(rawp[30,1], 6, nchar(rawp[30,1])),
                      substr(rawp[31,1], 7, nchar(rawp[31,1])), substr(rawp[32,1], 9, nchar(rawp[32,1])),
                      substr(rawp[33,1], 12, nchar(rawp[33,1])), substr(rawp[34,1], 13, nchar(rawp[34,1])),
                      substr(rawp[35,1], 9, nchar(rawp[35,1])), substr(rawp[36,1], 8, nchar(rawp[36,1])),
                      substr(rawp[37,1], 8, nchar(rawp[37,1]))))
        try(varsind <- which(varstf == "True"))
        try(vars <- varslist[varsind])
  try(rethead <- substr(rawp[46,1], 13, nchar(rawp[46,1]))); try(endunits <- substr(rawp[5,1], 15, nchar(rawp[5,1])))
  try(epoch <- as.numeric(substr(rawp[6,1], 15, nchar(rawp[6,1]))))
  try(out1 <- ifelse(substr(rawp[38,1], 13, nchar(rawp[38,1]))  == "True", ".csv", NA))
  try(out2 <- ifelse(substr(rawp[39,1], 13, nchar(rawp[39,1]))  == "True", ".tab", NA))
  try(out3 <- ifelse(substr(rawp[40,1], 13, nchar(rawp[40,1]))  == "True", ".txt", NA))
  try(out4 <- ifelse(substr(rawp[41,1], 14, nchar(rawp[41,1]))  == "True", ".xlsx", NA))
  try(outform <- as.vector(na.omit(c(out1,out2,out3,out4))))
  try(outdir <- paste0(gsub("\\\\", "/",substr(rawp[50,1], 20, nchar(rawp[50,1]))),"/"))
  try(multithread <- substr(rawp[48,1], 12, nchar(rawp[48,1])))
  try(extenin <- tools::file_ext(filenames[1]))

  vlist <- list(samprate = samprate, startrow = startrow, xcol = xcol, ycol = ycol, zcol = zcol, vmcol = vmcol, tstamp = tstamp, resamp = resamp,
                resampfz = resampfz, calibration = calibration, vmonly = vmonly, startunits = startunits, endunits = endunits,
                tcol = tcol, tform = tform, drow = drow, dform = dform, trow = trow, tform2 = tform2,
                sdate = sdate, stime = stime, vars = vars, rethead = rethead, epoch = epoch, extenin = extenin,
                outform = outform, outdir = outdir, filenames = filenames, multithread = multithread)

  ###Get OS###
  ses <- Sys.info()[['sysname']]

  ###Get number of cores###
  cores <- parallel::detectCores()

  ###Get Indices for Files###
  plen <- 1:length(vlist$filenames)
  plenmax <- max(plen)

  ####Progress Bar####
  n_iter <- length(plen) # Number of iterations
  pb <- winProgressBar(title = "PADDP Raw Data Processing", # Window title
                       label = "Percentage completed", # Window label
                       min = 0,      # Minimum value of the bar
                       max = n_iter, # Maximum value of the bar
                       initial = 0,  # Initial value of the bar
                       width = 300L) # Width of the window

  out <- tryCatch({
    ####Function to Process Files####
    for(i in plen){
      files <- vlist$filenames[i]

      ###Compute Initial Variables####
      cols <- data.frame(cols = c(vlist$xcol,vlist$ycol,vlist$zcol),
                         collabs = c("X","Y","Z"))
      cols2 <- na.omit(cols)

      if(vlist$extenin == "csv" | vlist$extenin == "tab" |
         vlist$extenin == "dat" | vlist$extenin == "txt"){
      ###Find the number of observations in a file as fast as possible - memory efficient###
      filelen <- nrow(data.table::fread(files, select=cols2[1,1], skip=(vlist$startrow - 1),
                                        showProgress=F)); gc()
      effilelen <- trunc(filelen/(vlist$samprate))*(vlist$samprate);

      ###Create Chunk Indices###
      chnksval <- 10000000; chnksize <- trunc(chnksval/(vlist$samprate))*(vlist$samprate)
      bchnks <- trunc(effilelen/chnksize)-1; chnkseq <- 1:bchnks;
      chnkint <- chnkseq*chnksize; chnkfull <- c(0, chnkint, effilelen)
      chnkfullsec <- c(0, chnkint/vlist$samprate, effilelen/vlist$samprate)
      chnkbot <- c(0, chnkint-(vlist$samprate*120)); chnktop <- c(chnkint+(vlist$samprate*120), effilelen)

      if(effilelen < (chnksval)){
        chnkbot <- 0
        chnktop <- effilelen
      } else{
        chnkbot <- chnkbot
        chnktop <- chnktop
      }
      } else {
        chnkbot <- 1
      }

      ###Create Loop For Processing to the Second Level###
      res1 = list()
      res2 = list()
      nchunks <- 1:length(chnkbot)

      mprocfunc <- function(nchunks){
        iterval <- nchunks[1]
        if(vlist$extenin == "csv" | vlist$extenin == "tab" |
           vlist$extenin == "dat" | vlist$extenin == "txt"){
        ####Get Appropriate Extension for Passing to Fread####
        substrRight <- function(x, n){
          substr(x, nchar(x)-n+1, nchar(x))
        }
        flext <- substrRight(files, 3)
        sepval <- ifelse(flext=="csv", ",",
                         ifelse(flext=="tab", "\t", ""))
        ####Read-in the Data#####
        datint <- data.table::fread(files, sep = sepval, select=na.omit(cols$cols), skip=(chnkbot[iterval]+(vlist$startrow - 1)),
                                    nrows=((chnktop[iterval]-chnkbot[iterval])), col.names=as.character(cols2$collabs)); gc()

        dat <- if(vlist$startunits == "milli-g"){
          cvmgtog <- function(x){
            x / 1000
          }
          data.frame(apply(datint, 2, cvmgtog))
        } else if(vlist$startunits == "m/s^2"){
          cvmstog <- function(x){
            x / 9.81
          }
          data.frame(apply(datint, 2, cvmstog))
        } else {
          data.frame(datint)
        }

        ######Fix the Issue Below
        ###Resample Data if Needed####
        dat1 <- if((vlist$resamp == "True") & (vlist$resampfz != vlist$samprate) & (vlist$resampfz >= 30)){
          rsampdat1 <- function(x){
            gsignal::resample(x, vlist$resampfz, vlist$samprate);
          }
          test <- data.frame(apply(dat, 2, rsampdat1))
        } else if((vlist$resamp == "True") & (vlist$resampfz != vlist$samprate) & (vlist$resampfz < 30) & (vlist$samprate < 30)){
          rsampdat2 <- function(x){
            gsignal::resample(x, 30, vlist$samprate);
          }
         data.frame(apply(dat, MARGIN = 2, FUN = rsampdat2))
        } else if((vlist$resamp == "True") & (vlist$resampfz != vlist$samprate) & (vlist$resampfz < 30) & (vlist$samprate >= 30)){
          dat
        } else if((vlist$resamp == "True") & (vlist$resampfz == vlist$samprate)){
          dat
        } else if(vlist$resamp == "False"){
          dat
        } else{
          NULL
        }

        finsamprate <- if((vlist$resamp == "True") & (vlist$resampfz != vlist$samprate) & (vlist$resampfz >= 30)){
          vlist$resampfz
        } else if((vlist$resamp == "True") & (vlist$resampfz != vlist$samprate) & (vlist$resampfz < 30) & (vlist$samprate < 30)){
          30
        } else if((vlist$resamp == "True") & (vlist$resampfz != vlist$samprate) & (vlist$resampfz < 30) & (vlist$samprate >= 30)){
          vlist$samprate
        } else if((vlist$resamp == "True") & (vlist$resampfz == vlist$samprate)){
          vlist$samprate
        } else if(vlist$resamp == "False"){
          vlist$samprate
        } else{
          NULL
        }

        ####Resample for Counts#####
        dat3 <- if((finsamprate != 30 | finsamprate != 40 | finsamprate != 50 |
                    finsamprate != 60 | finsamprate != 70 | finsamprate != 80 |
                    finsamprate != 90 | finsamprate != 100) &
                   (sum(vlist$vars=="Counts")==1 | sum(vlist$vars=="Counts LFE")==1)==T){
          rsampdat3 <- function(x){
            gsignal::resample(x, 30, vlist$samprate)
          }
          data.frame(apply(dat1, 2, rsampdat3))
        } else{
          dat1
        }

        ####Store the Dat3 Sampling Frequency#####
        dat3fz <- (nrow(dat3)/nrow(dat1)) * finsamprate

        ####Restrict Resampled Data to Complete Data for the Epoch Specified#####
        dat1 <- head(dat1, trunc(nrow(dat1)/(finsamprate*vlist$epoch))*(finsamprate*vlist$epoch))
        dat3 <- head(dat3, trunc(nrow(dat3)/(dat3fz*vlist$epoch))*(dat3fz*vlist$epoch))

        } else if(vlist$extenin == "gt3x"){
          ###Read Data In####
          ###Need to track Sample Rate Through#####
          suppressWarnings(gtdat1 <- read.gt3x::read.gt3x(files, imputeZeroes=T, add_light=T)); gc()
          ####Get Data We Need####
          gtfz <- attr(gtdat1, "sample_rate"); gtstime <- as.POSIXct(attr(gtdat1, "start_time"), tz="UTC")
          gtlength <- length(attr(gtdat1, "time_index"))
          gtdat <- data.frame(gtdat1[1:gtlength, 1:3]) #, LUX = attr(gtdat1, "light_data"))
          ####Resample To Desired Frequency#####
          dat1 <- if(gtfz == vlist$resampfz | vlist$resamp == "False"){
            gtdat
          } else{
            X <- round2(gsignal::resample(gtdat$X, gtfz, vlist$resampfz), 3); gc()
            Y <- round2(gsignal::resample(gtdat$Y, gtfz, vlist$resampfz), 3); gc()
            Z <- round2(gsignal::resample(gtdat$Z, gtfz, vlist$resampfz), 3); gc()
            dat <- data.frame(X = X, Y = Y, Z = Z)
            rm(X,Y,Z); gc()
            dat
          }

          finsamprate <- if((vlist$resamp == "True") & (vlist$resampfz != gtfz) & (vlist$resampfz >= 30)){
            vlist$resampfz
          } else if((vlist$resamp == "True") & (vlist$resampfz != gtfz) & (vlist$resampfz < 30) & (gtfz < 30)){
            30
          } else if((vlist$resamp == "True") & (vlist$resampfz != gtfz) & (vlist$resampfz < 30) & (gtfz >= 30)){
            gtfz
          } else if((vlist$resamp == "True") & (vlist$resampfz == gtfz)){
            gtfz
          } else if(vlist$resamp == "False"){
            gtfz
          } else{
            NULL
          }

          ####Resample for Counts#####
          dat3 <- if((finsamprate != 30 | finsamprate != 40 | finsamprate != 50 |
                      finsamprate != 60 | finsamprate != 70 | finsamprate != 80 |
                      finsamprate != 90 | finsamprate != 100) &
                     (sum(vlist$vars=="COUNTS")==1 | sum(vlist$vars=="COUNTS_LF")==1)==T){
            rsampdat3 <- function(x){
              gsignal::resample(x, 30, gtfz)
            }
            data.frame(apply(dat1, 2, rsampdat3))
          } else{
            dat1
          }

          ####Store the Dat3 Sampling Frequency#####
          dat3fz <- (nrow(dat3)/nrow(dat1)) * finsamprate

          ####Restrict Resampled Data to Complete Data for the Epoch Specified#####
          dat1 <- head(dat1, trunc(nrow(dat1)/(finsamprate*vlist$epoch))*(finsamprate*vlist$epoch))
          dat3 <- head(dat3, trunc(nrow(dat3)/(dat3fz*vlist$epoch))*(dat3fz*vlist$epoch))

        } else if(vlist$extenin == "cwa"){
          ###Read Data In####
          invisible(gtdat1len <- ceiling(((GGIRread::readAxivity(files)$header$blocks)*120)/300)+1); gc()
          invisible(gtdat1 <- GGIRread::readAxivity(files, end = gtdat1len))
          ####Get Data We Need####
          gtfz <- gtdat1$header$frequency; gtstime <- as.POSIXct(gtdat1$header$start, tz="UTC")
          gtlength <- dim(gtdat1$data)[1]
          ####Resample To Desired Frequency#####
          dat1 <- if(gtfz == vlist$resampfz | vlist$resamp == "False"){
            dat <- gtdat1$data[,2:4]
            names(dat) <- c("X","Y","Z")
            dat
          } else{
            X <- round2(gsignal::resample(gtdat1$data$x, vlist$resampfz, gtfz), 3); gc()
            Y <- round2(gsignal::resample(gtdat1$data$y, vlist$resampfz, gtfz), 3); gc()
            Z <- round2(gsignal::resample(gtdat1$data$z, vlist$resampfz, gtfz), 3); gc()
            #light <- round2(gsignal::resample(gtdat1$data$light, vlist$resampfz, gtfz), 0); gc()
            #battery <- round2(gsignal::resample(gtdat1$data$battery, vlist$resampfz, gtfz), 2); gc()
            #temp <- round2(gsignal::resample(gtdat1$data$temp, vlist$resampfz, gtfz), 1); gc()
            #time <- seq(gtdat1$data$time[1], gtdat1$data$time[gtlength] + 100, 1/vlist$resampfz); gc()
            #time <- head(time, length(x)); gc()
            dat <- data.frame(X = X, Y = Y, Z = Z)
            rm(X,Y,Z); gc()
            dat
          }; gc()

          finsamprate <- if((vlist$resamp == "True") & (vlist$resampfz != gtfz) & (vlist$resampfz >= 30)){
            vlist$resampfz
          } else if((vlist$resamp == "True") & (vlist$resampfz != gtfz) & (vlist$resampfz < 30) & (gtfz < 30)){
            30
          } else if((vlist$resamp == "True") & (vlist$resampfz != gtfz) & (vlist$resampfz < 30) & (gtfz >= 30)){
            gtfz
          } else if((vlist$resamp == "True") & (vlist$resampfz == gtfz)){
            gtfz
          } else if(vlist$resamp == "False"){
            gtfz
          } else{
            NULL
          }

          ####Resample for Counts#####
          dat3 <- if((finsamprate != 30 | finsamprate != 40 | finsamprate != 50 |
                      finsamprate != 60 | finsamprate != 70 | finsamprate != 80 |
                      finsamprate != 90 | finsamprate != 100) &
                     (sum(vlist$vars=="COUNTS")==1 | sum(vlist$vars=="COUNTS_LF")==1)==T){
            rsampdat3 <- function(x){
              gsignal::resample(x, 30, gtfz)
            }
            data.frame(apply(dat1, 2, rsampdat3))
          } else{
            dat1
          }

          ####Store the Dat3 Sampling Frequency#####
          dat3fz <- (nrow(dat3)/nrow(dat1)) * finsamprate

          ####Restrict Resampled Data to Complete Data for the Epoch Specified#####
          dat1 <- head(dat1, trunc(nrow(dat1)/(finsamprate*vlist$epoch))*(finsamprate*vlist$epoch))
          dat3 <- head(dat3, trunc(nrow(dat3)/(dat3fz*vlist$epoch))*(dat3fz*vlist$epoch))

        } else if(vlist$extenin == "bin"){
          ###Read Data In####
          invisible(gtdat1 <- GENEAread::read.bin(files, verbose=F)); gc()
          ####Get Data We Need####
          gtfz <- gtdat1$freq; gtstime <- as.POSIXct(unlist(gtdat1$header[4, 1]), format="%Y-%m-%d %H:%M:%S", origin = "1970-01-01", tz="UTC")
          gtlength <- dim(gtdat1$data.out)[1]
          ####Resample To Desired Frequency#####
          dat1 <- if(gtfz == vlist$resampfz | vlist$resamp == "False"){
            dat <- data.frame(gtdat1$data.out[, 2:4]); gc()
            names(dat) <- c("X","Y","Z")
            dat
          } else{
            X <- round2(gsignal::resample(gtdat1$data.out[1:gtlength,2], vlist$resampfz, gtfz), 3); gc()
            Y <- round2(gsignal::resample(gtdat1$data.out[1:gtlength,3], vlist$resampfz, gtfz), 3); gc()
            Z <- round2(gsignal::resample(gtdat1$data.out[1:gtlength,4], vlist$resampfz, gtfz), 3); gc()
            #light <- round2(gsignal::resample(gtdat1$data.out[1:gtlength,5], vlist$resampfz, gtfz)/5, 0)*5; gc()
            #button <- round2(gsignal::resample(gtdat1$data.out[1:gtlength,6], vlist$resampfz, gtfz), 0); gc()
            #temperature <- round2(gsignal::resample(gtdat1$data.out[1:gtlength,7], vlist$resampfz, gtfz), 1); gc()
            #timestamp <- seq(gtdat1$page.timestamps[1], (gtdat1$page.timestamps[1] + length(x)/vlist$resampfz) + 1, 1/vlist$resampfz); gc()
            #timestamp <- head(timestamp,length(x)); gc()
            #timestamp <- as.character(timestamp); gc()
            dat <- data.frame(X = X, Y = Y, Z = Z)
            rm(X,Y,Z); gc()
            dat
          }; gc()

          finsamprate <- if((vlist$resamp == "True") & (vlist$resampfz != gtfz) & (vlist$resampfz >= 30)){
            vlist$resampfz
          } else if((vlist$resamp == "True") & (vlist$resampfz != gtfz) & (vlist$resampfz < 30) & (gtfz < 30)){
            30
          } else if((vlist$resamp == "True") & (vlist$resampfz != gtfz) & (vlist$resampfz < 30) & (gtfz >= 30)){
            gtfz
          } else if((vlist$resamp == "True") & (vlist$resampfz == gtfz)){
            gtfz
          } else if(vlist$resamp == "False"){
            gtfz
          } else{
            NULL
          }

          ####Resample for Counts#####
          dat3 <- if((finsamprate != 30 | finsamprate != 40 | finsamprate != 50 |
                      finsamprate != 60 | finsamprate != 70 | finsamprate != 80 |
                      finsamprate != 90 | finsamprate != 100) &
                     (sum(vlist$vars=="COUNTS")==1 | sum(vlist$vars=="COUNTS_LF")==1)==T){
            rsampdat3 <- function(x){
              gsignal::resample(x, 30, gtfz)
            }
            data.frame(apply(dat1, 2, rsampdat3))
          } else{
            dat1
          }

          ####Store the Dat3 Sampling Frequency#####
          dat3fz <- (nrow(dat3)/nrow(dat1)) * finsamprate

          ####Restrict Resampled Data to Complete Data for the Epoch Specified#####
          dat1 <- head(dat1, trunc(nrow(dat1)/(finsamprate*vlist$epoch))*(finsamprate*vlist$epoch))
          dat3 <- head(dat3, trunc(nrow(dat3)/(dat3fz*vlist$epoch))*(dat3fz*vlist$epoch))

        } else {
          #####Nothing - Not a Recognized File Extension######
          NULL
        }

        ####Calculate Variables#####
        ####MAD###
        MAD <- if((sum(vlist$vars=="MAD")==1)==T){
          PAADPh::MADcalculate(x = dat1$X, y = dat1$Y, z = dat1$Z, hz = finsamprate, epoch = vlist$epoch) * 1000
        }        else{
          NULL
        } ; gc()

        ####sVM###
        SVM <- if((sum(vlist$vars=="SVM")==1)==T){
          PAADPh::SVMcalculate(x = dat1$X, y = dat1$Y, z = dat1$Z, hz = finsamprate, epoch = vlist$epoch) * 1000
        } else {
          NULL
        } ; gc()

        ####SVMgs###
        SVMgs <- if((sum(vlist$vars=="SVMgs")==1)==T){
          PAADPh::SVMgscalculate(x = dat1$X, y = dat1$Y, z = dat1$Z, hz = finsamprate, epoch = vlist$epoch)
        } else {
          NULL
        } ; gc()

        ####ENMO###
        ENMO <- if((sum(vlist$vars=="ENMO")==1)==T){
          PAADPh::ENMOcalculate(x = dat1$X, y = dat1$Y, z = dat1$Z, hz = finsamprate, epoch = vlist$epoch) * 1000
        } else {
          NULL
        } ; gc()

        ####LFENMO###
        LFENMO <- if((sum(vlist$vars=="LFENMO")==1)==T){
          PAADPh::LFENMOcalculate(x = dat1$X, y = dat1$Y, z = dat1$Z, hz = finsamprate, epoch = vlist$epoch) * 1000
        } else {
          NULL
        } ; gc()

        ####BFEN###
        BFEN <- if((sum(vlist$vars=="BFEN")==1)==T){
          PAADPh::BFENcalculate(x = dat1$X, y = dat1$Y, z = dat1$Z, hz = finsamprate, epoch = vlist$epoch) * 1000
        } else {
          NULL
        } ; gc()

        ####HFEN###
        HFEN <- if((sum(vlist$vars=="HFEN")==1)==T){
          PAADPh::HFENcalculate(x = dat1$X, y = dat1$Y, z = dat1$Z, hz = finsamprate, epoch = vlist$epoch) * 1000
        } else {
          NULL
        } ; gc()

        ####HFEN+###
        HFENplus <- if((sum(vlist$vars=="HFENp")==1)==T){
          PAADPh::HFENpluscalculate(x = dat1$X, y = dat1$Y, z = dat1$Z, hz = finsamprate, epoch = vlist$epoch) * 1000
        } else {
          NULL
        } ; gc()

        ####MIMS###
        ####Why Is This Not Working####
        MIMS <- if((sum(vlist$vars=="MIMS")==1)==T){
          PAADPh::MIMScalculate(x = dat1$X, y = dat1$Y, z = dat1$Z, vm = NULL, hz = finsamprate, epoch = vlist$epoch, dynr2 = c(-8,8))
        } else{
          NULL
        } ; gc()

        ####Counts###
        CTSX <- if((sum(vlist$vars=="COUNTS" | vlist$vars=="COUNTS_LF")>=1)==T){
          PAADPh::agcountscalculate(x = dat3$X, hz = finsamprate, epoch = vlist$epoch)
        } else {
          NULL
        }

        CTSXNF <- if((sum(vlist$vars=="COUNTS")==1)==T){
          unlist(CTSX[1])
        } else {
          NULL
        }

        CTSXLFE <- if((sum(vlist$vars=="COUNTS_LF")==1)==T){
          unlist(CTSX[2])
        } else {
          NULL
        }

        CTSY <- if((sum(vlist$vars=="COUNTS" | vlist$vars=="COUNTS_LF")>=1)==T){
          PAADPh::agcountscalculate(x = dat3$Y, hz = finsamprate, epoch = vlist$epoch)
        } else {
          NULL
        }

        CTSYNF <- if((sum(vlist$vars=="COUNTS")==1)==T){
          unlist(CTSY[1])
        } else {
          NULL
        }

        CTSYLFE <- if((sum(vlist$vars=="COUNTS_LF")==1)==T){
          unlist(CTSY[2])
        } else {
          NULL
        }

        CTSZ <- if((sum(vlist$vars=="COUNTS" | vlist$vars=="COUNTS_LF")>=1)==T){
          PAADPh::agcountscalculate(x = dat3$Z, hz = finsamprate, epoch = vlist$epoch)
        } else {
          NULL
        }

        CTSZNF <- if((sum(vlist$vars=="COUNTS")==1)==T){
          unlist(CTSZ[1])
        } else {
          NULL
        }

        CTSZLFE <- if((sum(vlist$vars=="COUNTS_LF")==1)==T){
          unlist(CTSZ[2])
        } else {
          NULL
        }

        CTSVMNF <- if((sum(vlist$vars=="COUNTS")==1)==T){
          sqrt(CTSXNF^2 + CTSYNF^2 + CTSZNF^2)
        } else {
          NULL
        }

        CTSVMLFE <- if((sum(vlist$vars=="COUNTS_LF")==1)==T){
          sqrt(CTSXLFE^2 + CTSYLFE^2 + CTSZLFE^2)
        } else {
          NULL
        }

        ####Sedentary Sphere###
        SSPHERE <- if((sum(vlist$vars=="SED_SPHERE")==1)==T){
          PAADPh::SSPHEREcalculate(x = dat1$X, y = dat1$Y, z = dat1$Z, hz = finsamprate)
        } else {
          NULL
        }

        ####Steps Experimental Filter - Waist###
        ####Need to Investigate This Function###
        #STEPS_WAIST_EXP <- if((sum(vlist$vars=="WAISTEPS2")==1)==T){
        #  PAADPh::acc2steps(x = dat1$X, y = dat1$Y, z = dat1$Z, Hz = finsamprate, epoch = vlist$epoch)
        #} else {
        #  NULL
        #}
        STEPS_WAIST_EXP <- NULL

        STEP1 <- if((sum(vlist$vars=="WAISTEPS1" | vlist$vars=="WRISTEPS")>=1)==T){
          PAADPh::STEPcalculate(x = dat1$X, y = dat1$Y, z = dat1$Z, hz = finsamprate, epoch = vlist$epoch)
        } else {
          NULL
        }

        ####Steps Waist###
        STEPWAIST <- if((sum(vlist$vars=="WAISTEPS1")==1)==T){
          unlist(STEP1[1])
        } else {
          NULL
        }

        ####Steps Wrist###
        STEPWRIST <- if((sum(vlist$vars=="WRISTEPS")==1)==T){
          unlist(STEP1[2])
        } else {
          NULL
        }
        ###Identify What is Going on Here####
        ###Get the Appropriate Sequence Number####
        SEQN <- ((chnkfull[1+1])-(chnkfull[1]))/(finsamprate*vlist$epoch)

        ###Combine Data####
        fdat1 <- list(MAD = MAD, SVM = SVM, SVMgs = SVMgs, ENMO = ENMO, LFENMO = LFENMO,
                      BFEN = BFEN, HFEN = HFEN, HFENplus = HFENplus, MIMS = MIMS,
                      CTSXNF = CTSXNF, CTSYNF = CTSYNF, CTSZNF = CTSZNF, CTSVMNF = CTSVMNF,
                      CTSXLFE = CTSXLFE, CTSYLFE = CTSYLFE, CTSZLFE = CTSZLFE, CTSVMLFE = CTSVMLFE,
                      STEPS_WAIST_EXP = STEPS_WAIST_EXP,
                      STEPWAIST = STEPWAIST, STEPWRIST = STEPWRIST)
        try(fdat1[sapply(fdat1, is.null)] <- NULL, silent=T)
        try(fdat1 <- do.call(cbind.data.frame, fdat1), silent=T)
        try(fdat1 <- if(chnkfull[iterval]==0){
          head(fdat1, chnkfull[iterval+1]/(vlist$samprate*vlist$epoch))
        } else if(chnkfull[iterval+1]==max(chnkfull)){
          tail(fdat1, (chnkfull[iterval+1]-chnkfull[iterval])/(vlist$samprate*vlist$epoch))
        } else {
          tail(head(fdat1, ((chnkfull[iterval+1]+120*vlist$samprate)-chnkfull[iterval])/(vlist$samprate*vlist$epoch)),
               ((chnkfull[iterval+1]-chnkfull[iterval])/(vlist$samprate*vlist$epoch)))
        },silent=T)
        res1[[length(res1)+1]] =  fdat1

        fdat2 <- list(SSPHERE = SSPHERE)
        try(fdat2[sapply(fdat2, is.null)] <- NULL, silent=T)
        try(fdat2 <- do.call(cbind.data.frame, fdat2), silent=T)
        try(fdat2 <- if(chnkfull[iterval]==0){
          head(fdat2, chnkfull[iterval+1]/(vlist$samprate*15))
        } else if(chnkfull[iterval+1]==max(chnkfull)){
          tail(fdat2, (chnkfull[iterval+1]-chnkfull[iterval])/(vlist$samprate*15))
        } else {
          tail(head(fdat2, ((chnkfull[iterval+1]+120*15)-chnkfull[iterval])/(vlist$samprate*15)),
               ((chnkfull[iterval+1]-chnkfull[iterval])/(vlist$samprate*15)))
        }, silent=T)
        res2[[length(res2)+1]] =  fdat2

        ####Combine the Lists####
        return(list(res1=res1, res2=res2))
      }

      #####Lapply Varations for Single/Multi-Threading & Various Platforms#####
      #####Linux and MacOS should be faster via mclapply (not possible on windows)####
      if(ses=="Windows" & vlist$multithread=="Yes"){
        cl <- parallel::makePSOCKcluster(trunc(0.66*cores))
        parallel::clusterExport(cl, c('mprocfunc','nchunks','vlist','cols','res1','res2','cols2',
                                      'chnksize','chnkfull','chnkfullsec','chnkbot','chnktop','files'),
                                envir=environment())
        system.time(resfull <- parallel::parLapply(cl, nchunks, mprocfunc))
        parallel::stopCluster(cl)
      } else if(vlist$multithread=="False"){
        resfull <- lapply(nchunks, mprocfunc)
      } else {
        resfull <- parallel::mclapply(nchunks, mprocfunc, mc.cores=trunc(cores/2))
      }

      ###Collapse the Different Data Streams####
      ###Remove Null Variables####
      resint1 <- unlist(resfull, recursive=F)
      res1seq <- seq(1, length(resint1), 3); res2seq <- seq(2, length(resint1), 3)

      resint2 <- list(do.call("rbind", (do.call("rbind", resint1[res1seq]))),
                      do.call("rbind", (do.call("rbind", resint1[res2seq])))); gc()
      resint2 <- Filter(function(x) dim(x)[2] > 0, resint2)
      resc1 <- do.call("cbind", resint2)
      resc <- data.frame(SEQN = 1:nrow(resc1),resc1)

      ####Work on Timestamp####
      ####Get Appropriate Extension for Passing to Fread####
      if(vlist$extenin == "csv" | vlist$extenin == "tab" |
         vlist$extenin == "dat" | vlist$extenin == "txt"){
      substrRight <- function(x, n){
        substr(x, nchar(x)-n+1, nchar(x))
      }
      flext <- substrRight(files, 3)
      sepval <- ifelse(flext=="csv", ",",
                       ifelse(flext=="tab", "\t", ""))

      ####Extract All the Appropriate Start Dates/Times/Rows/Formats Etc.######
      tstampst <- if(vlist$tstamp=="Yes1"){
        ####Timestamp in Column###
        tcol <- vlist$tcol####Indicated Timestamp Column
        tformlow <- data.frame(stringr::str_locate_all(vlist$tform, "[a-z]"))
        tformhigh <- data.frame(stringr::str_locate_all(vlist$tform, "[A-Z]"))
        tform <- rbind(tformlow,tformhigh); tchars <- tform[with(tform, order(start,end)), ]$start
        tcharsv <- unlist(lapply(tchars, function(x) substr(vlist$tform, x, x)))
        tformlen <- nchar(vlist$tform); ntchars <- setdiff(1:tformlen, tchars)
        ntcharsv <- unlist(lapply(ntchars, function(x) substr(vlist$tform, x, x)))
        pchars <- tchars-0.5; pcharsv <- (rep("%", length(pchars)))
        tformdat <- data.frame(charsord = c(tchars,ntchars,pchars),
                               response = c(tcharsv,ntcharsv,pcharsv))
        tformdat <- tformdat[with(tformdat, order(charsord)), ]
        tformfin <- paste(tformdat$response, collapse="")
        tdat <- read.table(files, sep = sepval, header=F, skip=vlist$startrow-1, nrows = 1)[1,1]
        as.POSIXct(tdat, format=tformfin, tz="UTC")
      } else if(vlist$tstamp=="Yes2"){
        ###Starting Date/Time in Header####
        drow <- vlist$drow######Indicated Date Row in Data####
        dformlow <- data.frame(stringr::str_locate_all(vlist$dform, "[a-z]"))
        dformhigh <- data.frame(stringr::str_locate_all(vlist$dform, "[A-Z]"))
        dform <- rbind(dformlow,dformhigh); dchars <- dform[with(dform, order(start,end)), ]$start
        dcharsv <- unlist(lapply(dchars, function(x) substr(vlist$dform, x, x)))
        dformlen <- nchar(vlist$dform); ndchars <- setdiff(1:dformlen, dchars)
        ndcharsv <- unlist(lapply(ndchars, function(x) substr(vlist$dform, x, x)))
        dpchars <- dchars-0.5; dpcharsv <- (rep("%", length(dpchars)))
        dformdat <- data.frame(charsord = c(dchars,ndchars,dpchars),
                               response = c(dcharsv,ndcharsv,dpcharsv))
        dformdat <- dformdat[with(dformdat, order(charsord)), ]
        dformfin <- paste(dformdat$response, collapse="")
        ddat <- as.character(read.table(files, sep = sepval, header=F, skip=vlist$drow-1,nrows = 1)[1,1])
        sdval <- gsub("[^0-9.[:punct:]]","",ddat)

        trow <- vlist$trow####Indicated Timestamp Column
        tform2low <- data.frame(stringr::str_locate_all(vlist$tform2, "[a-z]"))
        tform2high <- data.frame(stringr::str_locate_all(vlist$tform2, "[A-Z]"))
        tform2 <- rbind(tform2low,tform2high); tchars2 <- tform2[with(tform2, order(start,end)), ]$start
        tcharsv2 <- unlist(lapply(tchars2, function(x) substr(vlist$tform2, x, x)))
        tform2len <- nchar(vlist$tform2); ntchars2 <- setdiff(1:tform2len, tchars2)
        ntcharsv2 <- unlist(lapply(ntchars2, function(x) substr(vlist$tform2, x, x)))
        pchars2 <- tchars2-0.5; pcharsv2 <- (rep("%", length(pchars2)))
        tform2dat <- data.frame(charsord = c(tchars2,ntchars2,pchars2),
                                response = c(tcharsv2,ntcharsv2,pcharsv2))
        tform2dat <- tform2dat[with(tform2dat, order(charsord)), ]
        tform2fin <- paste(tform2dat$response, collapse="")
        ttim <- as.character(read.table(files, sep = sepval, header=F, skip=vlist$trow-1,nrows = 1)[1,1])
        tival <- gsub("[^0-9.[:punct:]]","",ttim)

        stival <- paste(sdval, tival)
        stistruct <- paste(dformfin,tform2fin)
        as.POSIXct(stival, format=stistruct, tz="UTC")
      } else if(vlist$tstamp=="Yes3"){
        ###Starting Date/Time input by User####
        sdate <- vlist$sdate
        stime <- vlist$stime
        sdtime <- paste(sdate,stime)
        as.POSIXct(sdtime, format="%Y-%m-%d %H:%M:%S", tz="UTC")
      }else{
        NULL
      }

      #####Create the Actual Timestamp#####
      dtimestamp <- if(is.null(tstampst)==F & is.null(as.POSIXct(as.character(tstampst),format="%Y-%m-%d %H:%M:%S"))==F){
        as.character(paste(seq(tstampst, (tstampst+(nrow(resc)-1)*vlist$epoch), vlist$epoch)))
      } else if(is.null(tstampst)){
        NULL
      } else{
        stop("Timestamp Error: Check Input Date/Time Parameters")
      }
      } else if(vlist$extenin == "gt3x" | vlist$extenin == "cwa" | vlist$extenin == "bin"){
      dtimestamp <- as.character(paste(seq(gtstime, (gtstime + (nrow(resc)-1)*vlist$epoch), vlist$epoch)))
      } else{
        stop("Timestamp Error: Check Input File Integrity")
      }

      #####Final Data#####
      if(is.null(dtimestamp)){
        findat <- resc
      } else {
        findat <- data.frame(Timestamp = dtimestamp,resc)
      }

      ####Write the Data to File####
      fname <- if(nchar(vlist$extenin == 3)){
      paste0(vlist$outdir,"/",substr(basename(files),1,nchar(basename(files))-4),vlist$epoch,"sec")
      } else if(nchar(vlist$extenin == 4)){
      paste0(vlist$outdir,"/",substr(basename(files),1,nchar(basename(files))-5),vlist$epoch,"sec")
      } else {
        NULL
      }

      ####CSV Files#####
      if((sum(vlist$outform==".csv")==1)==T & vlist$rethead=="False"){
        data.table::fwrite(findat, paste0(fname,".csv"), sep=",",
                           showProgress=F,verbose=F)
      } else if((sum(vlist$outform==".csv")==1)==T & vlist$rethead=="True"){
        hdat <- readr::read_lines(files, skip=0, n_max=(vlist$startrow-1),
                                  na=character())
        write.table(hdat, paste0(fname,".csv"), sep=",", col.names=F, row.names=F)
        data.table::fwrite(findat, paste0(fname,".csv"), sep=",", append=T, col.names=T,
                           showProgress=F,verbose=F)
      } else {
        NULL
      }

      ####TAB Files#####
      if((sum(vlist$outform==".tab")==1)==T & vlist$rethead=="False"){
        data.table::fwrite(findat, paste0(fname,".tab"), sep="\t",
                           showProgress=F,verbose=F)
      } else if((sum(vlist$outform==".tab")==1)==T & vlist$rethead=="True"){
        hdat <- readr::read_lines(files, skip=0, n_max=(vlist$startrow-1),
                                  na=character())
        write.table(hdat, paste0(fname,".tab"), sep="\t", col.names=F, row.names=F)
        data.table::fwrite(findat, paste0(fname,".tab"), sep="\t", append=T, col.names=T,
                           showProgress=F,verbose=F)
      } else {
        NULL
      }

      ####TXT Files#####
      if((sum(vlist$outform==".txt")==1)==T & vlist$rethead=="False"){
        data.table::fwrite(findat, paste0(fname,".txt"), sep=" ",
                           showProgress=F,verbose=F)
      } else if((sum(vlist$outform==".txt")==1)==T & vlist$rethead=="True"){
        hdat <- readr::read_lines(files, skip=0, n_max=(vlist$startrow-1),
                                  na=character())
        write.table(hdat, paste0(fname,".txt"), sep=" ", col.names=F, row.names=F)
        data.table::fwrite(findat, paste0(fname,".txt"), sep=" ", append=T, col.names=T,
                           showProgress=F,verbose=F)
      } else {
        NULL
      }

      ####XLSX Files#####
      if((sum(vlist$outform==".xlsx")==1)==T){
        writexl::write_xlsx(findat, paste0(fname,".xlsx"))
      } else {
        NULL
      }
     pctg <- paste(round(i/n_iter *100, 0), "% completed")
     setWinProgressBar(pb, i, label = pctg) # The label will override the label set on the
    }
    close(pb) # Close the connection
},
  error = function(err.msg){
    write(toString(err.msg), errpath, append=TRUE)
  })
}

procrawdata()
