
###Initial Code####

###Make Sure to Grab the R-Portable LibPath Only###
wdir <- getwd()
libfin <- paste0(substr(wdir,1,nchar(wdir) - 3),"library")
.libPaths(libfin)

######Grab the Correct Directories for Accessing Commands#####
procepochdata <- function(){
  ######Grab the Correct Directories for Accessing Commands#####
  ###setwd("G:/PAADP/R/R-4.3.3/bin")
  wdir <- getwd()
  outpath <- paste0(substr(wdir,1,nchar(wdir) - 13),"commands/epoch/epoch_output.txt")
  epochp <- read.table(outpath, header = F, sep="\t")
  
  ####Grab the Error Log Path and Create Dump File - Populated As Needed###
  errpath <- paste0(substr(wdir,1,nchar(wdir) - 13),"errors/epoch/errors.txt")
  
  ###Clear out the Error File If There######
  file.remove(dir(paste0(substr(wdir,1,nchar(wdir) - 13),"errors/epoch/"),
                  pattern = "*.txt", full.names=T))  
  
  #####Initialize Raw Data Processing Inputs########
  filen <- NA;
  pat1 <- NA; pat2 <- NA; pat2b <- NA; pat2c <- NA; pat2d <- NA; pat2e <- NA; pat2f <- NA; pat2g <- NA
  startloc <- NA; stoploc <- NA; stoploc1 <- NA; stoploc2 <- NA; stoploc3 <- NA; stoploc4 <- NA; stoploc5 <- NA; stoploc6 <- NA; stoploc7 <- NA
  fnum <- NA; files <- NA; filenames <- NA
  epochinput <- NA; startrow <- NA; tstamp <- NA
  tcol <- NA; tform <- NA; drow <- NA; dform <- NA; sdate <- NA
  trow <- NA; tform2 <- NA; stime <- NA;
  var1 <- NA; var1col <- NA; var2 <- NA; var2col <- NA
  integrate <- NA; intepoch <- NA; wearmark <- NA; slpwkwearalgo <- NA; wearalgo <- NA
  v1cutset <- NA; v1labels <- NA; v1cuts <- NA
  v2cutset <- NA; v2labels <- NA; v2cuts <- NA
  daily <- NA; nonmiss <- NA; wearmin <- NA; total <- NA
  mindays <- NA; outform <- NA; outdir <- NA; multithread <- NA; extenin <- NA;

  #####Identify the System########
  #####Only Really Works for Windows Currently###
  sysin <- paste(Sys.info()[1])
  
  if(sysin == "Windows"){
    try(filen <- gsub("\\\\", "/", substr(epochp[12,1], 18, nchar(epochp[12,1]))))
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
  try(epochinput <- as.numeric(substr(epochp[1,1], 22, nchar(epochp[1,1]))))
  try(startrow <- as.numeric(substr(epochp[19,1], 17, nchar(epochp[19,1]))))
  try(tstamp <- ifelse(substr(epochp[36,1], 12, nchar(epochp[36,1])) == "True", "Yes1",
                       ifelse(substr(epochp[37,1], 12, nchar(epochp[37,1])) == "True", "Yes2",
                ifelse(substr(epochp[38,1], 13, nchar(epochp[38,1])) == "True", "Yes3", "No"))))
  try(tcol <- as.numeric(substr(epochp[20,1], 19, nchar(epochp[20,1]))))
  try(tform <- substr(epochp[2,1], 17, nchar(epochp[2,1])))
  try(drow <- as.numeric(substr(epochp[21,1], 11, nchar(epochp[21,1]))))
  try(dform <- substr(epochp[3,1], 12, nchar(epochp[3,1])))
  try(trow <- as.numeric(substr(epochp[22,1], 11, nchar(epochp[22,1]))))
  try(tform2 <- substr(epochp[4,1], 12, nchar(epochp[4,1])))
  try(sdate <- substr(epochp[13,1], 13, nchar(epochp[13,1])))
  try(stime <- substr(epochp[13,1], 13, nchar(epochp[13,1])))
  try(var1 <- substr(epochp[5,1], 15, nchar(epochp[5,1])))
  try(var1col <- as.numeric(substr(epochp[23,1], 12, nchar(epochp[23,1]))))
  try(var2 <- substr(epochp[6,1], 15, nchar(epochp[6,1])))
  try(var2col <- as.numeric(substr(epochp[24,1], 12, nchar(epochp[24,1]))))
  try(integrate <- substr(epochp[28,1], 12, nchar(epochp[28,1])))
  try(intepoch <- as.numeric(substr(epochp[7,1], 23, nchar(epochp[7,1]))))
  try(wearmark <- substr(epochp[29,1], 12, nchar(epochp[29,1])))
  try(slpwkwearalgo <- substr(epochp[8,1], 28, nchar(epochp[8,1])))
  try(wearalgo <- substr(epochp[9,1], 17, nchar(epochp[9,1])))
  try(v1cutset <- substr(epochp[10,1], 18, nchar(epochp[10,1])))
  try(v1labels <- substr(epochp[15,1], 12, nchar(epochp[15,1])))
  try(v1cuts <- substr(epochp[17,1], 21, nchar(epochp[17,1])))
  try(v2cutset <- substr(epochp[11,1], 18, nchar(epochp[11,1])))
  try(v2labels <- substr(epochp[16,1], 12, nchar(epochp[16,1])))
  try(v2cuts <- substr(epochp[18,1], 21, nchar(epochp[18,1])))
  try(daily <- substr(epochp[30,1], 16, nchar(epochp[30,1])))
  try(nonmiss <- as.numeric(substr(epochp[25,1], 26, nchar(epochp[25,1]))))
  try(wearmin <- as.numeric(substr(epochp[26,1], 19, nchar(epochp[26,1]))))
  try(total <- substr(epochp[31,1], 16, nchar(epochp[31,1])))
  try(mindays <- as.numeric(substr(epochp[27,1], 17, nchar(epochp[27,1]))))
  try(out1 <- ifelse(substr(epochp[32,1], 13, nchar(epochp[32,1]))  == "True", ".csv", NA))
  try(out2 <- ifelse(substr(epochp[33,1], 13, nchar(epochp[33,1]))  == "True", ".tab", NA))
  try(out3 <- ifelse(substr(epochp[34,1], 13, nchar(epochp[34,1]))  == "True", ".txt", NA))
  try(out4 <- ifelse(substr(epochp[35,1], 14, nchar(epochp[35,1]))  == "True", ".xlsx", NA))
  try(outform <- as.vector(na.omit(c(out1,out2,out3,out4))))
  try(outdir <- paste0(gsub("\\\\", "/",substr(epochp[42,1], 20, nchar(epochp[42,1]))),"/"))
  try(multithread <- substr(epochp[40,1], 12, nchar(epochp[40,1])))
  try(extenin <- tools::file_ext(filenames[1]))

  vlist <- list(filenames = filenames, epochinput = epochinput, startrow = startrow,
                tstamp = tstamp, tcol = tcol, tform = tform, drow = drow,
                dform = dform, trow = trow, tfrom2 = tform2, sdate = sdate,
                stime = stime, var1 = var1, var1col = var1col, var2 = var2,
                var2col = var2col, integrate = integrate, intepoch = intepoch,
                wearmark = wearmark, slpwkwearalgo = slpwkwearalgo,
                wearalgo = wearalgo, v1cutset = v1cutset, v1labels = v1labels,
                v1cuts = v1cuts, v2cutset = v2cutset, v2labels = v2labels,
                v2cuts = v2cuts, daily = daily, nonmiss = nonmiss, wearmin = wearmin,
                total = total, mindays = mindays, outform = outform,
                outdir = outdir, multithread = multithread, extenin = extenin)
  
  ###Get OS###
  ses <- Sys.info()[['sysname']]
  
  ###Get number of cores###
  cores <- parallel::detectCores()
  
  ###Get Indices for Files###
  plen <- 1:length(vlist$filenames)
  plenmax <- max(plen)
  
  ####Progress Bar####
  n_iter <- length(plen) # Number of iterations
  pb <- winProgressBar(title = "PADDP Epoch Data Processing", # Window title
                       label = "Percentage completed", # Window label
                       min = 0,      # Minimum value of the bar
                       max = n_iter, # Maximum value of the bar
                       initial = 0,  # Initial value of the bar
                       width = 300L) # Width of the window
  
  out <- tryCatch({
    ####Initialize The Collection Lists#####
    dailylist <- list()
    dailywidelist <- list()
    totallist <- list()
    totalwidelist <- list()
    ####Function to Process Files####
    for(i in plen){
      try(files <- vlist$filenames[i])
      
      ####Read-In The Data####
      try(dat <- if(vlist$extenin == "csv" | vlist$extenin == "tab" |
                vlist$extenin == "dat" | vlist$extenin == "txt"){
                data.frame(data.table::fread(files, skip=(vlist$startrow - 1), showProgress=F))    
      } else if(vlist$extenin == "xls" | vlist$extenin == "xlsx"){
                data.frame(readxl::read_excel(files, skip=(vlist$startrow - 1)))
      })
      
      #####Get the Participant Name From the File Name#####
      try(fsnamestart <- substr(files, max(unlist(gregexpr('/', files)))+1, nchar(files)))
      try(fsname <- if(vlist$extenin == "csv" | vlist$extenin == "tab" |
                   vlist$extenin == "dat" | vlist$extenin == "txt" |
                   vlist$extenin == "xls" ){
                    substr(fsnamestart, 1, nchar(fsnamestart)-4)   
      }   else if(vlist$extenin == "xlsx"){
                    substr(fsnamestart, 1, nchar(fsnamestart)-5)  
      })
      
      ####Clean Up the Name####
      rmkey1 <- "RAW"; rmkey2 <- "raw"; rmkey3 <- "1sec"; rmkey4 <- "2sec"
      rmkey5 <- "3sec"; rmkey6 <- "4sec"; rmkey7 <- "5sec"; rmkey8 <- "6sec"
      rmkey9 <- "10sec"; rmkey10 <- "15sec"; rmkey11 <- "30sec"; rmkey12 <- "60sec"
      rmkey13 <- "90sec"; rmkey14 <- "120sec"; rmkey15 <- "."
      
      try(fsname <- stringr::str_remove(fsname, rmkey1)); try(fsname <- stringr::str_remove(fsname, rmkey2))
      try(fsname <- stringr::str_remove(fsname, rmkey14)); try(fsname <- stringr::str_remove(fsname, rmkey13))
      try(fsname <- stringr::str_remove(fsname, rmkey12)); try(fsname <- stringr::str_remove(fsname, rmkey11))
      try(fsname <- stringr::str_remove(fsname, rmkey10)); try(fsname <- stringr::str_remove(fsname, rmkey9))
      try(fsname <- stringr::str_remove(fsname, rmkey8)); try(fsname <- stringr::str_remove(fsname, rmkey7))
      try(fsname <- stringr::str_remove(fsname, rmkey6)); try(fsname <- stringr::str_remove(fsname, rmkey5))
      try(fsname <- stringr::str_remove(fsname, rmkey4)); try(fsname <- stringr::str_remove(fsname, rmkey3))
      try(fsname <- stringr::str_remove(fsname, stringr::fixed(rmkey15)))

      ####Extract the Needed Data - Timestamp & Variables####
      ####Extract the Data####
      var1name <- NA; var1 <- NA
      try(var1name <- vlist$var1)
      try(var1 <- dat[,vlist$var1col])
      var2name <- NA; var2 <- NA
      try(var2name <- vlist$var2)
      try(var2 <- dat[,vlist$var2col])
      ####Timestamp#####
      try(timestamp <- if(vlist$tstamp == "Yes1"){
        dat[,vlist$tcol]
      } else if(vlist$tstamp == "Yes2"){
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
        fintstamp <- as.POSIXct(stival, format=stistruct, tz="UTC")
        seq(fintstamp, (fintstamp+(nrow(dat)-1)*vlist$epoch), vlist$epoch)
        } else if(vlist$tstamp == "Yes3"){
          ###Starting Date/Time input by User####
        sdate <- vlist$sdate
        stime <- vlist$stime
        sdtime <- paste(sdate,stime)
        fintstamp <- as.POSIXct(sdtime, format="%Y-%m-%d %H:%M:%S", tz="UTC")
        seq(fintstamp, (fintstamp+(nrow(dat)-1)*vlist$epoch), vlist$epoch)
        } else{
        NULL
        })
      ####Grab the Actual Epoch#####
      epochchk <- NA
      try(epochchk <- timestamp[2]-timestamp[1])
      try(epochact <- if(attr(epochchk,"units") == "mins"){
                    as.numeric(epochchk)*60
      } else if(attr(epochchk,"units") == "hours"){
                    as.numeric(epochchk)*3600
      } else if(attr(epochchk,"units") == "days"){
                    as.numeric(epochchk)*86400
      } else if(attr(epochchk,"units") == "secs"){
                    as.numeric(epochchk)
      })
      
      ####Integrate, Wear Mark, Sleep Mark########
              ####Define Whole Number Check####
              is.wholenumber <- function(x, tol = .Machine$double.eps^0.5)  abs(x - round(x)) < tol
              ####Define Sum Variables#####
              sumvars <- c("COUNTS","COUNTS LF","SVMgs","MIMS","STEPS")
              meanvars <- c("SVM","ENMO","LFENMO","BFEN","HFEN","HFEN+","MAD","Custom")
              ####Define Integration Factor####
              try(integratefact <- vlist$intepoch/epochact)
              
          #####Variables 1 & 2 Integrate Functions######
      var1int <- NA
      try(var1int <- if((vlist$integrate == "True") & (epochact < vlist$intepoch) &
                    (is.wholenumber(vlist$intepoch/epochact) & (var1name %in% sumvars))){
                      PAADPh::round2(colSums(matrix(var1, nrow = integratefact)),3)                      
      } else if((vlist$integrate == "True") & (epochact < vlist$intepoch) &
           (is.wholenumber(vlist$intepoch/epochact) & (var1name %in% meanvars))){
                      PAADPh::round2(colMeans(matrix(var1, nrow = integratefact)),3)  
      } else{
                      var1
      })
              
      var2int <- NA        
      try(var2int <- if((vlist$integrate == "True") & (epochact < vlist$intepoch) &
                      (is.wholenumber(vlist$intepoch/epochact) & (var2name %in% sumvars))){
                        PAADPh::round2(colSums(matrix(var2, nrow = integratefact)),3)                   
      } else if((vlist$integrate == "True") & (epochact < vlist$intepoch) &
                        (is.wholenumber(vlist$intepoch/epochact) & (var2name %in% meanvars))){
                        PAADPh::round2(colMeans(matrix(var2, nrow = integratefact)),3) 
      } else{
                        var2
      })
      
      timestampint <- NA
      try(timestampint <- if((vlist$integrate == "True") & (epochact < vlist$intepoch) &
                         (is.wholenumber(vlist$intepoch/epochact) & (var2name %in% sumvars))){
                          timestamp[seq(1,length(timestamp),integratefact)]                 
      } else if((vlist$integrate == "True") & (epochact < vlist$intepoch) &
                (is.wholenumber(vlist$intepoch/epochact) & (var2name %in% meanvars))){
                          timestamp[seq(1,length(timestamp),integratefact)]    
      } else{
                          timestamp
      })
      
      epochchk2 <- NA; epochactint <- NA
      try(epochchk2 <- timestampint[2]-timestampint[1])
      try(epochactint <- if(attr(epochchk2,"units") == "mins"){
        as.numeric(epochchk2)*60
      } else if(attr(epochchk2,"units") == "hours"){
        as.numeric(epochchk2)*3600
      } else if(attr(epochchk2,"units") == "days"){
        as.numeric(epochchk2)*86400
      } else if(attr(epochchk2,"units") == "secs"){
        as.numeric(epochchk2)
      })
      
          #####Sleep/Wake Algorithms######
      slkwkwear <- NA
      try(slpwkwear <- if(vlist$wearmark == "True" & vlist$slpwkwearalgo == "None"){
                  NA
      } else if(vlist$wearmark == "True" & vlist$slpwkwearalgo == "NHANES"){
                  NA
      } else if(vlist$wearmark == "True" & vlist$slpwkwearalgo == "Tudor-Locke & Barreira"){
                  NA
      } else{
                  NA
      })
      
      #var2int2 <- if(vlist$wearmark == "True" & vlistslpwkwearalgo == "None"){
      #            var2int
      #} else if(vlist$wearmark == "True" & vlistslpwkwearalgo == "NHANES"){
      #            var2int
      #} else if(vlist$wearmark == "True" & vlistslpwkwearalgo == "Tudor-Locke & Barreira"){
      #            var2int
      #} else{
      #            var2int
      #}
      
          ######Wear Algorithms#######
          #####Prepare Data for Choi Algorithm#####
      wdat <- NA
      try(wdat <- data.frame(timestamp = timestamp, var1 = var1int))
          #####Wear time function#####
      wear <- NA
      try(wear <- if((var1name == "COUNTS" | var1name=="COUNTS LF") & vlist$wearmark == "True" &
                 vlist$wearalgo == "Troiano (2008)"){
                  accelerometry::weartime(var1int, window = 60, tol = 2, tol_upper = 99,
                                          nci = FALSE, days_distinct = F, units = (1440 * (60/epochact)))          
      } else if((var1name == "COUNTS" | var1name=="COUNTS LF") & vlist$wearmark == "True" &
                vlist$wearalgo == "Choi (2011)"){
                  choidat <- PhysicalActivity::wearingMarking(wdat, frame = 90, perMinuteCts = (60/epochact),
                                                   TS = "timestamp", cts = "var1")
                  ifelse(choidat$wearing=="w",1,0)
      } else if((var1name == "COUNTS" | var1name=="COUNTS LF") & vlist$wearmark == "True" &
                vlist$wearalgo == "20 Min (0 Counts)"){
                  accelerometry::weartime(var1int, window = 20, tol = 0, tol_upper = 99999,
                                       nci = FALSE, days_distinct = F, units = (1440 * (60/epochact))) 
      } else if((var1name == "COUNTS" | var1name=="COUNTS LF") & vlist$wearmark == "True" &
                vlist$wearalgo == "30 Min (0 Counts)"){
                  accelerometry::weartime(var1int, window = 30, tol = 0, tol_upper = 99999,
                                       nci = FALSE, days_distinct = F, units = (1440 * (60/epochact))) 
      } else if((var1name == "COUNTS" | var1name=="COUNTS LF") & vlist$wearmark == "True" &
                vlist$wearalgo == "60 Min (0 Counts)"){
                  accelerometry::weartime(var1int, window = 60, tol = 0, tol_upper = 99999,
                                       nci = FALSE, days_distinct = F, units = (1440 * (60/epochact))) 
      } else {
        NA
      })
      
      ####Variable Cutpoints######
      ####Grab the Variable #1 Cutpoints#####
      v1labs <- NA; v1labels <- NA; v1ct1 <- NA; v1ct <- NA
      v1ctinclusive <- NA; v1ctexclusive <- NA; v1ctdat <- NA
      try(v1labs <- as.vector(unlist(strsplit(vlist$v1labels, "\\,"))))
      try(v1labels <- as.vector(unlist(sapply(v1labs, function(x){trimws(x)}))))
      try(v1ct1 <- strsplit(vlist$v1cuts, "\\,"))
      try(v1ct <- as.vector(unlist(sapply(v1ct1, function(x){trimws(x)}))))
      try(v1ctinclusive <- stringr::str_detect(v1ct, "-"))
      try(v1ctexclusive <- stringr::str_detect(v1ct, "\\+"))
      try(v1ctdat <- data.frame(seqn = 1:length(v1labs),v1labs,v1ct,v1ctinclusive,v1ctexclusive))
      
      cutfunc1 <- function(x){
                   retdat <-  if(x$v1ctinclusive == T){
                                 low <- unlist(strsplit(x$v1ct,"\\-"))[1]; v1low <- as.numeric(gsub("[^0-9.-]", "", low))
                                 high <- unlist(strsplit(x$v1ct,"\\-"))[2]; v1high <- as.numeric(gsub("[^0-9.-]", "", high))
                                 v1labels <- x$v1labs
                                 data.frame(v1labels,v1low,v1high)
                              } else {
                                 v1low <- as.numeric(gsub("[^0-9.-]", "", x$v1ct))
                                 v1high <- as.numeric(Inf)
                                 v1labels <- x$v1labs
                                 data.frame(v1labels,v1low,v1high)
                              }
                   seqn <- x$seqn[1]
                   retdat <- data.frame(seqn, retdat)
      }
      v1cutstot <- data.frame(seqn = 0, v1labels = "ALL", v1low = 0, v1high = Inf)
      v1cuts <- NA; v1cutsb <- NA
      try(v1cuts <- v1cutstot)
      try(v1cutsb <- invisible(do.call('rbind', by(v1ctdat, v1ctdat$seqn, cutfunc1))))
      try(v1cuts <- rbind(v1cuts, v1cutsb))
      try(v1cuts <- na.omit(v1cuts))
      
      v2labs <- NA; v2labels <- NA; v2ct1 <- NA; v2ct <- NA
      v2ctinclusive <- NA; v2ctexclusive <- NA; v2ctdat <- NA
      try(v2labs <- as.vector(unlist(strsplit(vlist$v2labels, "\\,"))))
      try(v2labels <- as.vector(unlist(sapply(v2labs, function(x){trimws(x)}))))
      try(v2ct1 <- strsplit(vlist$v2cuts, "\\,"))
      try(v2ct <- as.vector(unlist(sapply(v2ct1, function(x){trimws(x)}))))
      try(v2ctinclusive <- stringr::str_detect(v2ct, "-"))
      try(v2ctexclusive <- stringr::str_detect(v2ct, "\\+"))
      try(v2ctdat <- data.frame(seqn = 1:length(v2labs),v2labs,v2ct,v2ctinclusive,v2ctexclusive))
      
      cutfunc2 <- function(x){
                  retdat <-  if(x$v2ctinclusive == T){
                                low <- unlist(strsplit(x$v2ct,"\\-"))[1]; v2low <- as.numeric(gsub("[^0-9.-]", "", low))
                                high <- unlist(strsplit(x$v2ct,"\\-"))[2]; v2high <- as.numeric(gsub("[^0-9.-]", "", high))
                                v2labels <- x$v2labs
                                data.frame(v2labels,v2low,v2high)
                              } else {
                                v2low <- as.numeric(gsub("[^0-9.-]", "", x$v2ct))
                                v2high <- as.numeric(Inf)
                                v2labels <- x$v2labs
                                data.frame(v2labels,v2low,v2high)
                              }
                  seqn <- x$seqn[1]
                  retdat <- data.frame(seqn, retdat)
      }
      v2cutstot <- data.frame(seqn = 0, v2labels = "ALL", v2low = 0, v2high = Inf)
      v2cuts <- NA; v2cutsb <- NA
      try(v2cuts <- v2cutstot)
      try(v2cutsb <- invisible(do.call('rbind', by(v2ctdat, v2ctdat$seqn, cutfunc2))))
      try(v2cuts <- rbind(v2cuts,v2cutsb))
      try(v2cuts <- na.omit(v2cuts))
  
      ####Summarize to the Daily Level#########
      dates <- NA; v1daydat <- NA
      try(dates <- factor(substr(timestampint,1,10)))
      try(v1daydat <- data.frame(dates, var1int, wear))
    
      v1dayfunc <- function(x){
                              v1d <- plyr::ddply(v1cuts, plyr::.(seqn), function(v1cuts){
                                                  intensity_labels <- v1cuts$v1labels
                                                  mins <- sum((x$var1int >= v1cuts$v1low) & (x$var1int <= v1cuts$v1high) &
                                                                     x$wear == 1) / (60/epochactint)
                                                        intsub <- subset(x, var1int >= v1cuts$v1low & var1int <= v1cuts$v1high &
                                                                         wear == 1)
                                                  intvalues <- if(var1name %in% sumvars){
                                                                      sum(intsub$var1int)
                                                  } else{
                                                                      mean(intsub$var1int)
                                                  }
                                                  data.frame(intensity_labels,mins,intvalues)
                              })
                      variable <- rep(var1name, nrow(v1d))
                      varnum <- rep("v1", nrow(v1d))
                      obs <- rep(nrow(x),nrow(v1d))
                      wear <- sum(x$wear == 1) / (60/epochactint)
                  data.frame(variable, varnum, obs, wear, v1d)}
      v1dat <- NA
      try(v1dat <- plyr::ddply(v1daydat, plyr::.(dates), v1dayfunc))
      
      v2daydat <- NA
      try(v2daydat <- data.frame(dates, var2int, wear))
      
      v2dayfunc <- function(x){
        v2d <- plyr::ddply(v2cuts, plyr::.(seqn), function(v2cuts){
          intensity_labels <- v2cuts$v2labels
          mins <- sum(x$var2int >= v2cuts$v2low & x$var2int <= v2cuts$v2high &
                              x$wear == 1) / (60/epochactint)
          intsub <- subset(x, var2int >= v2cuts$v2low & var2int <= v2cuts$v2high &
                             wear == 1)
          intvalues <- if(var2name %in% sumvars){
            sum(intsub$var2int)
          } else{
            mean(intsub$var2int)
          }
          data.frame(intensity_labels,mins,intvalues)
        })
        variable <- rep(var2name, nrow(v2d))
        varnum <- rep("v2", nrow(v2d))
        obs <- rep(nrow(x),nrow(v2d))
        wear <- sum(x$wear == 1) / (60/epochactint)
        data.frame(variable, varnum, obs, wear, v2d)}
      v2dat <- NA
      try(v2dat <- plyr::ddply(v2daydat, plyr::.(dates), v2dayfunc))
      
      ####Merge the Two Data Streams#####
      vdaydat <- NA
      try(vdaydat <- v1dat)
      try(vdaydat <- rbind(v1dat, v2dat))
      try(vdaydat <- data.frame(PID = rep(fsname, nrow(vdaydat)),
                                          vdaydat))
      try(vdaydat_wide <- reshape(vdaydat, idvar = c("dates","variable","varnum"),
                                 v.names = c("mins","intvalues"), drop = "seqn",
                                 timevar = c("intensity_labels"), direction="wide"))
      names(vdaydat_wide) <- stringr::str_replace_all(names(vdaydat_wide), stringr::fixed(" "), "")

      ####Summarize Across Valid Days##########
      ###Prep the Appropriate Indicators#####
      nonmiss <- NA; wearmin <- NA
      vnonmiss <- NA; vwearmin <- NA
      mindays <- NA
      try(nonmiss <- vlist$nonmiss); try(wearmin <- vlist$wearmin)
      try(mindays <- vlist$mindays)
      try(vnonmiss <- ifelse(vdaydat$obs < nonmiss, 0, 1))
      try(vwearmin <- ifelse(vdaydat$wear < wearmin, 0, 1))
      daydat <- NA
      try(daydat <- data.frame(vdaydat, vnonmiss, vwearmin))
      
      totfunc <- function(x){
                        PID <- x$PID[1]
                        variable <- x$variable[1]
                        varnum <- x$varnum[1]
                        validdays <- sum(x$vnonmiss == 1 & x$vwearmin == 1)
                        intensity_labels <- x$intensity_labels[1]
                        ####Apply Validity Criteria###
                        vx <- subset(x, vnonmiss == 1 & vwearmin == 1)
                        obs_mins <- mean(vx$obs, na.rm=T)
                        wear_mins <- mean(vx$wear, na.rm=T)
                        mins <- mean(vx$mins, na.rm=T)
                        intvalues <- mean(vx$intvalues, na.rm=T)
                data.frame(PID, variable, varnum, validdays, obs_mins, 
                           wear_mins, intensity_labels, mins, intvalues)
      }
      totdat <- NA; totdat_wide <- NA
      try(totdat <- plyr::ddply(daydat, plyr::.(variable,varnum,intensity_labels), totfunc))
      try(totdat_wide <- reshape(totdat, idvar = c("variable","varnum"),
                             v.names = c("mins","intvalues"), sep = ".",
                             timevar = c("intensity_labels"), direction="wide"))
      names(totdat_wide) <- stringr::str_replace_all(names(totdat_wide), stringr::fixed(" "), "")
      ####Collect the Processed Data To Shuttle Out of For Loop#####
      dailylist[[i]] <- vdaydat
      dailywidelist[[i]] <- vdaydat_wide
      totallist[[i]] <- totdat
      totalwidelist[[i]] <- totdat_wide
      ####Update the Percentage Completion Indicator#####
      pctg <- paste(round(i/n_iter *100, 0), "% completed")
      setWinProgressBar(pb, i, label = pctg)
    }
    ######Collapse the Data In Each Stream######
    try(ddatlong <- data.frame(data.table::rbindlist(dailylist)))
    try(ddatwide <- data.frame(data.table::rbindlist(dailywidelist)))
    try(tdatlong <- data.frame(data.table::rbindlist(totallist)))  
    try(tdatwide <- data.frame(data.table::rbindlist(totalwidelist)))  
      
    ####Output the Summarized Data Sets######
    ####Write the Data to File####
    try(fsnamedaylong <- paste0(vlist$outdir,"daily","_long_",Sys.Date()))
    try(fsnamedaywide <- paste0(vlist$outdir,"daily","_wide_",Sys.Date()))
    try(fsnametotlong <- paste0(vlist$outdir,"total","_long_",Sys.Date()))
    try(fsnametotwide <- paste0(vlist$outdir,"total","_wide_",Sys.Date()))
    
    ####CSV Files#####
    try(if((sum(vlist$outform==".csv")==1)==T & vlist$total=="False"){
      write.table(ddatlong, paste0(fsnamedaylong,".csv"), sep=",", col.names=T,
                  row.names=F, quote=F, append=F)
      write.table(ddatwide, paste0(fsnamedaywide,".csv"), sep=",", col.names=T,
                  row.names=F, quote=F, append=F)
    } else if((sum(vlist$outform==".csv")==1)==T & vlist$total=="True"){
      write.table(ddatlong, paste0(fsnamedaylong,".csv"), sep=",", col.names=T,
                  row.names=F, quote=F, append=F)
      write.table(ddatwide, paste0(fsnamedaywide,".csv"), sep=",", col.names=T,
                  row.names=F, quote=F, append=F)
      write.table(tdatlong, paste0(fsnametotlong,".csv"), sep=",", col.names=T,
                  row.names=F, quote=F, append=F)
      write.table(tdatwide, paste0(fsnametotwide,".csv"), sep=",", col.names=T,
                  row.names=F, quote=F, append=F)
    } else {
      NULL
    })
    
    ####TAB Files#####
    try(if((sum(vlist$outform==".tab")==1)==T & vlist$total=="False"){
      write.table(ddatlong, paste0(fsnamedaylong,".tab"), sep="\t", col.names=T,
                  row.names=F, quote=F, append=F)
      write.table(ddatwide, paste0(fsnamedaywide,".tab"), sep="\t", col.names=T,
                  row.names=F, quote=F, append=F)
    } else if((sum(vlist$outform==".tab")==1)==T & vlist$total=="True"){
      write.table(ddatlong, paste0(fsnamedaylong,".tab"), sep="\t", col.names=T,
                  row.names=F, quote=F, append=F)
      write.table(ddatwide, paste0(fsnamedaywide,".tab"), sep="\t", col.names=T,
                  row.names=F, quote=F, append=F)
      write.table(tdatlong, paste0(fsnametotlong,".tab"), sep="\t", col.names=T,
                  row.names=F, quote=F, append=F)
      write.table(tdatwide, paste0(fsnametotwide,".tab"), sep="\t", col.names=T,
                  row.names=F, quote=F, append=F)
    } else {
      NULL
    })
    
    ####TXT Files#####
    try(if((sum(vlist$outform==".txt")==1)==T & vlist$total=="False"){
      write.table(ddatlong, paste0(fsnamedaylong,".txt"), sep=" ", col.names=T,
                  row.names=F, quote=F, append=F)
      write.table(ddatwide, paste0(fsnamedaywide,".txt"), sep=" ", col.names=T,
                  row.names=F, quote=F, append=F)
    } else if((sum(vlist$outform==".txt")==1)==T & vlist$total=="True"){
      write.table(ddatlong, paste0(fsnamedaylong,".txt"), sep=" ", col.names=T,
                  row.names=F, quote=F, append=F)
      write.table(ddatwide, paste0(fsnamedaywide,".txt"), sep=" ", col.names=T,
                  row.names=F, quote=F, append=F)
      write.table(tdatlong, paste0(fsnametotlong,".txt"), sep=" ", col.names=T,
                  row.names=F, quote=F, append=F)
      write.table(tdatwide, paste0(fsnametotwide,".txt"), sep=" ", col.names=T,
                  row.names=F, quote=F, append=F)
    } else {
      NULL
    })
    
    ####XLSX Files#####
    try(if((sum(vlist$outform==".xlsx")==1)==T & vlist$total=="False"){
      writexl::write_xlsx(ddatlong, paste0(fsnamedaylong,".xlsx"))
      writexl::write_xlsx(ddatwide, paste0(fsnamedaywide,".xlsx"))
    } else if((sum(vlist$outform==".xlsx")==1)==T & vlist$total=="True"){
      writexl::write_xlsx(ddatlong, paste0(fsnamedaylong,".xlsx"))
      writexl::write_xlsx(ddatwide, paste0(fsnamedaywide,".xlsx"))  
      writexl::write_xlsx(tdatlong, paste0(fsnametotlong,".xlsx"))
      writexl::write_xlsx(tdatwide, paste0(fsnametotwide,".xlsx"))  
    } else {
      NULL
    })
    
    ####Close the Progresss Bar####
    close(pb)
},
error = function(err.msg){
  write(toString(err.msg), errpath, append=TRUE)
})
}
 
procepochdata()   
      