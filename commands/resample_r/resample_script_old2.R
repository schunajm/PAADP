
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

###Resample Function###
procresampdata <- function(){
  ######Grab the Correct Directories for Accessing Commands#####
  wdir <- getwd()
  outpath <- paste0(substr(wdir,1,nchar(wdir) - 13),"commands/resample/resample_output.txt")
  rsap <- read.table(outpath, header = F, sep="\t")
  
  ####Grab the Error Log Path and Create Dump File - Populated As Needed###
  errpath <- paste0(substr(wdir,1,nchar(wdir) - 13),"errors/resample/errors.txt")
  
  ###Clear out the Error File If There######
  file.remove(dir(paste0(substr(wdir,1,nchar(wdir) - 13),"errors/resample/"),
                  pattern = "*.txt", full.names=T))
  
  #####Initialize Resampling Inputs########
  filen <- NA; pat1 <- NA; pat2 <- NA; pat2b <- NA; pat2c <- NA; pat2d <- NA; pat2e <- NA; pat2f <- NA; pat2g <- NA
  startloc <- NA; stoploc <- NA; stoploc1 <- NA; stoploc2 <- NA;
  stoploc3 <- NA; stoploc4 <- NA; stoploc5 <- NA; stoploc6 <- NA; stoploc7 <- NA; fnum <- NA; files <- NA; filenames <- NA; samprate <- NA; resampfz <- NA;
  vmdatonly <- NA; startrow <- NA; xcol <- NA; ycol <- NA; zcol <- NA; vmcol <- NA; tstamp <- NA; tcol <- NA; tform <- NA;
  drow <- NA; dform <- NA; trow <- NA; tform2 <- NA; sdate <- NA; stime <- NA; rethead <- NA; outform <- NA; matchadc <- NA;
  adcbit <- NA; dynrang <- NA; outdir <- NA; multithread <- NA
  
  #####Collect Data from the GUI#####
  #####Identify the System########
  #####Only Really Works for Windows Currently###
  sysin <- paste(Sys.info()[1])
  
  if(sysin == "Windows"){
    try(filen <- gsub("\\\\", "/", substr(rsap[6,1], 18, nchar(rsap[6,1]))))
    try(pat1 <- "([:upper:][:])"); try(pat2 <- "([.][g][t][3][x])"); try(pat2b <- "([.][b][i][n])"); try(pat2c <- "([.][c][w][a])")
    try(pat2d <- "([.][t][x][t])"); try(pat2e <- "([.][d][a][t])"); try(pat2f <- "([.][t][a][b])"); try(pat2g <- "([.][c][s][v])")
    try(startloc <- data.frame(stringr::str_locate_all(filen, pat1))); try(stoploc1 <- data.frame(stringr::str_locate_all(filen, pat2)))
    try(stoploc2 <- data.frame(stringr::str_locate_all(filen, pat2b))); try(stoploc3 <- data.frame(stringr::str_locate_all(filen, pat2c)))
    try(stoploc4 <- data.frame(stringr::str_locate_all(filen, pat2d))); try(stoploc5 <- data.frame(stringr::str_locate_all(filen, pat2e)))
    try(stoploc6 <- data.frame(stringr::str_locate_all(filen, pat2f))); try(stoploc7 <- data.frame(stringr::str_locate_all(filen, pat2g)))
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
  
  try(samprate <- as.numeric(substr(rsap[9,1], 14, nchar(rsap[9,1])))); try(resampfz <- as.numeric(substr(rsap[10,1], 16, nchar(rsap[10,1]))))
  try(vmdataonly <- substr(rsap[19,1], 15, nchar(rsap[19,1])))
  try(startrow <- as.numeric(substr(rsap[11,1], 17, nchar(rsap[11,1]))))
  try(xcol <- as.numeric(substr(rsap[12,1], 16, nchar(rsap[12,1])))); try(ycol <- as.numeric(substr(rsap[13,1], 16, nchar(rsap[13,1]))))
  try(zcol <- as.numeric(substr(rsap[14,1], 16, nchar(rsap[14,1])))); try(vmcol <- as.numeric(substr(rsap[15,1], 12, nchar(rsap[15,1]))))
  try(tstamp <- ifelse(substr(rsap[24,1], 12, nchar(rsap[24,1])) == "True", "Yes1",
                       ifelse(substr(rsap[25,1], 12, nchar(rsap[25,1])) == "True", "Yes2",
                              ifelse(substr(rsap[26,1], 13, nchar(rsap[26,1])) == "True", "Yes3", "No"))))
  try(tcol <- as.numeric(substr(rsap[16,1], 19, nchar(rsap[16,1])))); try(tform <- substr(rsap[1,1], 17, nchar(rsap[1,1])))            
  try(drow <- as.numeric(substr(rsap[17,1], 11, nchar(rsap[17,1])))); try(dform <- substr(rsap[2,1], 12, nchar(rsap[2,1])))
  try(trow <- as.numeric(substr(rsap[18,1], 11, nchar(rsap[18,1])))); try(tform2 <- substr(rsap[3,1], 12, nchar(rsap[3,1])))
  try(sdate <- substr(rsap[7,1], 13, nchar(rsap[7,1]))); try(stime <- substr(rsap[8,1], 13, nchar(rsap[8,1])))
  try(rethead <- substr(rsap[28,1], 13, nchar(rsap[28,1])))
  try(out1 <- ifelse(substr(rsap[20,1], 13, nchar(rsap[20,1]))  == "True", ".csv", NA))
  try(out2 <- ifelse(substr(rsap[21,1], 13, nchar(rsap[21,1]))  == "True", ".tab", NA))
  try(out3 <- ifelse(substr(rsap[22,1], 13, nchar(rsap[22,1]))  == "True", ".txt", NA))
  try(out4 <- ifelse(substr(rsap[23,1], 14, nchar(rsap[23,1]))  == "True", ".xlsx", NA))
  try(outform <- as.vector(na.omit(c(out1,out2,out3,out4))))
  try(matchadc <- substr(rsap[30,1], 10, nchar(rsap[30,1]))); try(adcbit <- as.numeric(substr(rsap[4,1], 11, 12)))
  try(dynrang <- substr(rsap[5,1], 16, nchar(rsap[5,1])))
  try(multithread <- substr(rsap[32,1], 12, nchar(rsap[32,1])))
  try(outdir <- paste0(gsub("\\\\", "/",substr(rsap[34,1], 20, nchar(rsap[34,1]))),"/"))
  
  vlist <- list(filenames = filenames, samprate = samprate, resampfz = resampfz, vmdataonly = vmdataonly, startrow = startrow,
                xcol = xcol, ycol = ycol, zcol = zcol, vmcol = vmcol, tstamp = tstamp, tcol = tcol,
                tform = tform, drow = drow, dform = dform, trow = trow, tform2 = tform2, sdate = sdate,
                stime = stime,  rethead = rethead, outform = outform, matchadc = matchadc, adcbit = adcbit, dynrang = dynrang,
                outdir = outdir, multithread = multithread)
  
  ###Get OS###
  ses <- Sys.info()[['sysname']]
  
  ###Get number of cores###
  cores <- parallel::detectCores()
  
  ###Get Indices for Files###
  plen <- 1:length(vlist$filenames)
  plenmax <- max(plen)
  
  ###Calculate ADC Resolution###
  bitval <- as.numeric(stringr::str_extract(vlist$adcbit,"[[:digit:]]+"))
  dynrange <- as.numeric(stringr::str_extract(vlist$dynrang, "[[:digit:]]+"))
  
  ####Progress Bar####
  n_iter <- length(plen) # Number of iterations
  pb <- winProgressBar(title = "PADDP Resampling", # Window title
                       label = "Percentage completed", # Window label
                       min = 0,      # Minimum value of the bar
                       max = n_iter, # Maximum value of the bar
                       initial = 0,  # Initial value of the bar
                       width = 300L) # Width of the window 
  
  out <- tryCatch({
    ####Function to Process Files####
    for(i in plen){
      files <- vlist$filenames[i]
      
      ####Get File Type####
      exten <- substr(files, nchar(files) - 3, nchar(files))
      
      #####Parse GT3X files#####
      if(exten == "gt3x"){
        ###Read Data In####
        suppressWarnings(gtdat1 <- read.gt3x::read.gt3x(files, imputeZeroes=T, add_light=T)); gc()
        ####Get Data We Need####
        gtfz <- attr(gtdat1, "sample_rate"); gtstime <- attr(gtdat1, "start_time")
        gtlength <- length(attr(gtdat1, "time_index"))
        gtdat <- data.frame(gtdat1[1:gtlength, 1:3], LUX = attr(gtdat1, "light_data"))
        ####Resample To Desired Frequency#####
        rtdat <- if(gtfz == vlist$resampfz){
          gtdat
        } else{
          X <- round(gsignal::resample(gtdat$X, gtfz, vlist$resampfz), 3); gc()
          Y <- round(gsignal::resample(gtdat$Y, gtfz, vlist$resampfz), 3); gc()
          Z <- round(gsignal::resample(gtdat$Z, gtfz, vlist$resampfz), 3); gc()
          LUX <- round(gsignal::resample(gtdat$LUX, gtfz, vlist$resampfz), 0); gc()
          dat <- data.frame(X = X, Y = Y, Z = Z, LUX = LUX)
          rm(X,Y,Z,LUX); gc()
          dat
        }
        ####Get Header Pieces#####
        gtL1 <- paste0("------------ Data File Created By PAADP v 1.0 date format M/d/yyyy at ",gtfz," Hz -----------")
        gtL2 <- paste0("Serial Number: ",as.character(attr(gtdat1, "header")[[1]]))
        gttime <- substr(attr(gtdat1, "start_time"), 12, 19)
        gtdate1 <- substr(attr(gtdat1, "start_time"), 1, 10)
        gtdate <- paste0(substr(gtdate1,6,7),"/",substr(gtdate1,9,10),"/",substr(gtdate1,1,4))
        gtL3 <- paste0("Start Time ", gttime); gtL4 <- paste0("Start Date ", gtdate)
        gtL5 <- paste0("Epoch Period (hh:mm:ss) 00:00:00")
        dltimest <- attr(gtdat1, "header")[[7]]
        dltime <- substr(dltimest, 12, 19)
        dldate1 <- substr(dltimest, 1, 10)
        dldate <- paste0(substr(dldate1,6,7),"/",substr(dldate1,9,10),"/",substr(dldate1,1,4))
        gtL6 <- paste0("Download Time ", dltime); gtL7 <- paste0("Download Date ", dldate); gtL8 <- "Current Memory Address: 0"
        gtL9 <- paste0("Current Battery Voltage ",attr(gtdat1,"header")[[3]],"     Mode = 12")
        gtL10 <- "--------------------------------------------------"; gtL11 <- cbind("Axis1","Axis2","Axis3","LUX")
        gthlist <- list(gtL1,gtL2,gtL3,gtL4,gtL5,gtL6,gtL7,gtL8,gtL9,gtL10,gtL11)
        ####Write to File####
        ####Get Output Directory and Filename####
        fname <- if(substr(vlist$outdir, nchar(vlist$outdir), nchar(vlist$outdir)) == "/"){
          paste0(vlist$outdir,substr(basename(files),1,nchar(basename(files))-5),vlist$resampfz,"Hz")
        } else{
          paste0(vlist$outdir,"/",substr(basename(files),1,nchar(basename(files))-5),vlist$resampfz,"Hz")
        }
        
        for(i in 1:length(vlist$outform)){
          extenout <- vlist$outform
          extenval <- if(extenout == ".csv"){
            ","
          } else if(extenout == ".tab"){
            "\t"
          } else if(extenout == ".txt" | extenout == ".dat"){
            " "
          }
          
          if(vlist$rethead == "True"){
            rowrd <- 1:(length(gthlist))
            gtheadwrite <- function(gthlist, fname, rowrd, extenout, extenval){
              x <- gthlist[[rowrd]]
              if(rowrd == 1){
                write.table(x, paste0(fname,extenout), sep = extenval, col.names=F, row.names=F, append=F, quote=F)
              } else{
                write.table(x, paste0(fname,extenout), sep = extenval, col.names=F, row.names=F, append=T, quote=F)
              }
            }
            invisible(lapply(rowrd, gtheadwrite, gthlist = gthlist, fname = fname, extenout = extenout, extenval = extenval))
            data.table::fwrite(rtdat, paste0(fname,extenout), append = T, sep = extenval, col.names=F,
                               row.names=F, quote = F, showProgress = F)
          } else {
            starttime <- attr(gtdat1, "start_time")
            Timestamp <- seq(starttime, starttime + (nrow(rtdat)-1)/vlist$resampfz + 1, (1/vlist$resampfz)); gc()
            Timestamp <- head(Timestamp, nrow(rtdat)); gc()
            Timestamp <- as.character(Timestamp); gc()
            rtdat <- data.frame(Timestamp,rtdat)
            data.table::fwrite(rtdat, paste0(fname,extenout), append = F, sep = extenval, col.names=T,
                               row.names=F, quote = F, showProgress = F)
          }
        }
      } else if(exten == ".bin"){
        ###Read Data In####
        invisible(gtdat1 <- GENEAread::read.bin(files, verbose=F)); gc()
        ####Get Data We Need####
        gtfz <- gtdat1$freq; gtstime <- as.POSIXct(unlist(gtdat1$header[4, 1]), format="%Y-%m-%d %H:%M:%S", origin = "1970-01-01", tz="UTC")
        gtlength <- dim(gtdat1$data.out)[1]
        ####Resample To Desired Frequency#####
        rtdat <- if(gtfz == vlist$resampfz){
          timestamp <- seq(gtdat1$page.timestamps[1], (gtdat1$page.timestamps[1] + gtlength/gtfz) + 1, 1/gtfz); gc()
          timestamp <- head(timestamp,gtlength); gc()
          timestamp <- as.character(timestamp); gc()
          dat1 <- data.frame(gtdat1$data.out[1:gtlength, 2:7]); gc()
          data.frame(timestamp, dat1)
        } else{
          x <- round(gsignal::resample(gtdat1$data.out[1:gtlength,2], vlist$resampfz, gtfz), 3); gc()
          y <- round(gsignal::resample(gtdat1$data.out[1:gtlength,3], vlist$resampfz, gtfz), 3); gc()
          z <- round(gsignal::resample(gtdat1$data.out[1:gtlength,4], vlist$resampfz, gtfz), 3); gc()
          light <- round(gsignal::resample(gtdat1$data.out[1:gtlength,5], vlist$resampfz, gtfz)/5, 0)*5; gc()
          button <- round(gsignal::resample(gtdat1$data.out[1:gtlength,6], vlist$resampfz, gtfz), 0); gc()
          temperature <- round(gsignal::resample(gtdat1$data.out[1:gtlength,7], vlist$resampfz, gtfz), 1); gc()
          timestamp <- seq(gtdat1$page.timestamps[1], (gtdat1$page.timestamps[1] + length(x)/vlist$resampfz) + 1, 1/vlist$resampfz); gc()
          timestamp <- head(timestamp,length(x)); gc()
          timestamp <- as.character(timestamp); gc()
          dat <- data.frame(timestamp = timestamp, x = x, y = y, z = z, light = light, button = button, temperature = temperature)
          rm(timestampx,y,z,light,button,temperature); gc()
          dat
        }; gc()
        ####Get Header Pieces#####
        gtL1 <- cbind("Device Type","GENEActiv"); gtL2 <- cbind("Device Model","X.X"); gtL3 <- cbind("Device Unique Serial Code",paste0(unlist(gtdat1$header[1,])))
        gtL4 <- cbind("Device Firmware Version","VerX.XX date ddmmmYY"); gtL5 <- cbind("Calibration Date","YYYY-mm-dd HH:MM:SS.s"); gtL6 <- cbind("Application name & version","PAADP v1.0")
        gtL7 <- " "; gtL8 <- " "; gtL9 <- " "; gtL10 <- " "; gtL11 <- cbind("Measurement Frequency",paste0(vlist$resampfz,".0 Hz"))
        gtL12 <- cbind("Start Time",paste0(gtstime)); gtL13 <- cbind("Last Measurement"," "); gtL14 <- cbind("Device Location Code",paste0(unlist(gtdat1$header[9,])))
        gtL15 <- cbind("Time Zone",paste0("GMT ",as.numeric(attr(gtdat1$header, "calibration")[1]))); gtL16 <- " "; gtL17 <- " "; gtL18 <- " "; gtL19 <- " "; gtL20 <- " "
        gtL21 <- cbind("Subject Code",paste0(unlist(gtdat1$header[10,]))); gtL22 <- cbind("Date of Birth",paste0(unlist(gtdat1$header[11,])))
        gtL23 <- cbind("Sex",paste0(unlist(gtdat1$header[12,]))); gtL24 <- cbind("Height",paste0(unlist(gtdat1$header[13,])))
        gtL25 <- cbind("Weight",paste0(unlist(gtdat1$header[14,]))); gtL26 <- cbind("Handedness Code",paste0(unlist(gtdat1$header[15,])))
        gtL27 <- cbind("Subject Notes",""); gtL28 <- " "; gtL29 <- " "; gtL30 <- " "
        gtL31 <- cbind("Study Centre",""); gtL32 <- cbind("Study Code",""); gtL33 <- cbind("Investigator ID",""); gtL34 <- cbind("Exercise Type","")
        gtL35 <- cbind("Config Operator ID",""); gtL36 <- cbind("Config Time",""); gtL37 <- cbind("Config Notes","Notes")
        gtL38 <- cbind("Extract Operator ID",""); gtL39 <- cbind("Extract Time",""); gtL40 <- cbind("Extract Notes","")
        gtL41 <- " "; gtL42 <- " "; gtL43 <- " "; gtL44 <- " "; gtL45 <- " "; gtL46 <- " "; gtL47 <- " "; gtL48 <- " "; gtL49 <- " "; gtL50 <- " "
        gtL51 <- cbind("Sensor type","MEMS accelerometer x-axis"); gtL52 <- cbind("Range","-8 to 8"); gtL53 <- cbind("Resolution","0.0039")
        gtL54 <- cbind("Units","g"); gtL55 <- "Additional information"; gtL56 <- cbind("Sensor type","MEMS accelerometer y-axis")
        gtL57 <- gtL52; gtL58 <- gtL53; gtL59 <- gtL54; gtL60 <- gtL55; gtL61 <- cbind("Sensor type","MEMS accelerometer z-axis")
        gtL62 <- gtL52; gtL63 <- gtL53; gtL64 <- gtL54; gtL65 <- gtL55; gtL66 <- cbind("Sensor type","Lux Photodiode 400nm - 1100nm")
        gtL67 <- cbind("Range","0 to 5000"); gtL68 <- cbind("Resolution","5"); gtL69 <- cbind("Units","lux"); gtL70 <- gtL60
        gtL71 <- cbind("Sensor type","User button event marker"); gtL72 <- cbind("Range","1 or 0"); gtL73 <- "Resolution"
        gtL74 <- "Units"; gtL75 <- cbind("Additional information","1=pressed"); gtL76 <- cbind("Sensor type","Linear active thermistor")
        gtL77 <- cbind("Range","0 to 70"); gtL78 <- cbind("Resolution","0.1"); gtL79 <- cbind("Units","deg. C"); gtL80 <- "Additional information"
        gtL81 <- " "; gtL82 <- " "; gtL83 <- " "; gtL84 <- " "; gtL85 <- " "; gtL86 <- " "; gtL87 <- " "; gtL88 <- " "; gtL89 <- " "; gtL90 <- " "
        gtL91 <- " "; gtL92 <- " "; gtL93 <- " "; gtL94 <- " "; gtL95 <- " "; gtL96 <- " "; gtL97 <- " "; gtL98 <- " "; gtL99 <- " "; gtL100 <- " "
        gthlist <- list(gtL1,gtL2,gtL3,gtL4,gtL5,gtL6,gtL7,gtL8,gtL9,
                        gtL10,gtL11,gtL12,gtL13,gtL14,gtL15,gtL16,gtL17,gtL18,gtL19,gtL20,gtL21,gtL22,gtL23,gtL24,gtL25,gtL26,gtL27,gtL28,gtL29,
                        gtL30,gtL31,gtL32,gtL33,gtL34,gtL35,gtL36,gtL37,gtL38,gtL39,gtL40,gtL41,gtL42,gtL43,gtL44,gtL45,gtL46,gtL47,gtL48,gtL49,
                        gtL50,gtL51,gtL52,gtL53,gtL54,gtL55,gtL56,gtL57,gtL58,gtL59,gtL60,gtL61,gtL62,gtL63,gtL64,gtL65,gtL66,gtL67,gtL68,gtL69,
                        gtL70,gtL71,gtL72,gtL73,gtL74,gtL75,gtL76,gtL77,gtL78,gtL79,gtL80,gtL81,gtL82,gtL83,gtL84,gtL85,gtL86,gtL87,gtL88,gtL89,
                        gtL90,gtL91,gtL92,gtL93,gtL94,gtL95,gtL96,gtL97,gtL98,gtL99,gtL100)
        ####Write to File####
        ####Get Output Directory and Filename####
        fname <- if(substr(vlist$outdir, nchar(vlist$outdir), nchar(vlist$outdir)) == "/"){
          paste0(vlist$outdir,substr(basename(files),1,nchar(basename(files))-4),vlist$resampfz,"Hz")
        } else{
          paste0(vlist$outdir,"/",substr(basename(files),1,nchar(basename(files))-4),vlist$resampfz,"Hz")
        }
        
        for(i in 1:length(vlist$outform)){
          extenout <- vlist$outform
          extenval <- if(extenout == ".csv"){
            ","
          } else if(extenout == ".tab"){
            "\t"
          } else if(extenout == ".txt" | extenout == ".dat"){
            " "
          }
          
          if(vlist$rethead == "True"){
            rowrd <- 1:(length(gthlist))
            gtheadwrite <- function(gthlist, fname, rowrd, extenout, extenval){
              x <- gthlist[[rowrd]]
              if(rowrd == 1){
                write.table(x, paste0(fname,extenout), sep = extenval, col.names=F, row.names=F, append=F, quote=F)
              } else{
                write.table(x, paste0(fname,extenout), sep = extenval, col.names=F, row.names=F, append=T, quote=F)
              }
            }
            invisible(lapply(rowrd, gtheadwrite, gthlist = gthlist, fname = fname, extenout = extenout, extenval = extenval))
            data.table::fwrite(rtdat, paste0(fname,extenout), append = T, sep = extenval, col.names=F,
                               row.names=F, quote = F, showProgress = F)
          } else {
            data.table::fwrite(rtdat, paste0(fname,extenout), append = F, sep = extenval, col.names=T,
                               row.names=F, quote = F, showProgress = F)
          }
        }
      } else if(exten == ".cwa"){
        ###Read Data In####
        invisible(gtdat1len <- ceiling(((GGIR::g.cwaread(files)$header$blocks)*120)/300)+1); gc()
        invisible(gtdat1 <- GGIR::g.cwaread(files, end = gtdat1len))
        ####Get Data We Need####
        gtfz <- gtdat1$header$frequency; gtstime <- as.POSIXct(gtdat1$header$start, tz="UTC")
        gtlength <- dim(gtdat1$data)[1]
        ####Resample To Desired Frequency#####
        rtdat <- if(gtfz == vlist$resampfz){
          gtdat1$data
        } else{
          x <- round(gsignal::resample(gtdat1$data$x, vlist$resampfz, gtfz), 3); gc()
          y <- round(gsignal::resample(gtdat1$data$y, vlist$resampfz, gtfz), 3); gc()
          z <- round(gsignal::resample(gtdat1$data$z, vlist$resampfz, gtfz), 3); gc()
          light <- round(gsignal::resample(gtdat1$data$light, vlist$resampfz, gtfz), 0); gc()
          battery <- round(gsignal::resample(gtdat1$data$battery, vlist$resampfz, gtfz), 2); gc()
          temp <- round(gsignal::resample(gtdat1$data$temp, vlist$resampfz, gtfz), 1); gc()
          time <- seq(gtdat1$data$time[1], gtdat1$data$time[gtlength] + 100, 1/vlist$resampfz); gc()
          time <- head(time, length(x)); gc()
          dat <- data.frame(time = time, x = x, y = y, z = z, light = light, battery = battery, temp = temp)
          rm(timestampx,y,z,light,button,temperature); gc()
          dat
        }; gc()
        ####Get Header Pieces#####
        gtL1 <- cbind("uniqueSerialCode",as.numeric(gtdat1$header[1])); gtL2 <- cbind("frequency",as.numeric(gtdat1$header[2]));
        gtL3 <- cbind("start",(gtdat1$header[3]))
        gtL4 <- cbind("device",as.character(gtdat1$header[4]))
        gtL5 <- cbind("firmwareVersion",as.numeric(gtdat1$header[5])); gtL6 <- cbind("blocks",as.numeric(gtdat1$header[6]))
        gtL7 <- cbind("accrange",as.numeric(gtdat1$header[7])); gtL8 <- cbind("hardwareType",as.character(gtdat1$header[8]))
        gthlist <- list(gtL1,gtL2,gtL3,gtL4,gtL5,gtL6,gtL7,gtL8)
        ####Write to File####
        ####Get Output Directory and Filename####
        fname <- if(substr(vlist$outdir, nchar(vlist$outdir), nchar(vlist$outdir)) == "/"){
          paste0(vlist$outdir,substr(basename(files),1,nchar(basename(files))-4),vlist$resampfz,"Hz")
        } else{
          paste0(vlist$outdir,"/",substr(basename(files),1,nchar(basename(files))-4),vlist$resampfz,"Hz")
        }
        
        for(i in 1:length(vlist$outform)){
          extenout <- vlist$outform
          extenval <- if(extenout == ".csv"){
            ","
          } else if(extenout == ".tab"){
            "\t"
          } else if(extenout == ".txt" | extenout == ".dat"){
            " "
          }
          
          if(vlist$rethead == "True"){
            rowrd <- 1:(length(gthlist))
            gtheadwrite <- function(gthlist, fname, rowrd, extenout, extenval){
              x <- gthlist[[rowrd]]
              if(rowrd == 1){
                write.table(x, paste0(fname,extenout), sep = extenval, col.names=F, row.names=F, append=F, quote=F)
              } else{
                write.table(x, paste0(fname,extenout), sep = extenval, col.names=F, row.names=F, append=T, quote=F)
              }
            }
            invisible(lapply(rowrd, gtheadwrite, gthlist = gthlist, fname = fname, extenout = extenout, extenval = extenval))
            data.table::fwrite(rtdat, paste0(fname,extenout), append = T, sep = extenval, col.names=T,
                               row.names=F, quote = F, showProgress = F)
          } else {
            data.table::fwrite(rtdat, paste0(fname,extenout), append = F, sep = extenval, col.names=T,
                               row.names=F, quote = F, showProgress = F)
          }
        }
      } else {
        
        ###Compute Initial Variables####
        col1 <- if(vlist$vmdataonly == "True"){
          vlist$vmcol
        } else{
          vlist$xcol
        }
        
        cols <- if(vlist$vmdataonly == "True"){
          data.frame(cols = c(vlist$vmcol),
                     collabs = c("VM"))
        } else{
          data.frame(cols = c(vlist$xcol,vlist$ycol,vlist$zcol),
                     collabs = c("X","Y","Z"))
        }
        cols2 <- na.omit(cols)
        
        ###Find the number of observations in a file as fast as possible - memory efficient###
        filelen <- nrow(data.table::fread(files, select=col1, skip=(vlist$startrow - 1), showProgress=F)); gc
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
        
        nchunks <- 1:length(chnkbot)
        itermax <- max(nchunks)
        iterlength <- length(nchunks)
        
        mprocfunc <- function(nchunks){
          iterval <- nchunks
          #print(iterval)
          ####Get Appropriate Extension for Passing to Fread####
          substrRight <- function(x, n){
            substr(x, nchar(x)-n+1, nchar(x))
          }
          flext <- substrRight(files, 3)
          sepval <- ifelse(flext=="csv", ",",
                           ifelse(flext=="tab", "\t", " "))
          ####Read-in the Data#####
          dat <- data.table::fread(files, sep = sepval, select=na.omit(cols$cols), skip=(chnkbot[iterval]+(vlist$startrow - 1)),
                                   nrows=((chnktop[iterval]-chnkbot[iterval])), col.names=as.character(cols2$collabs)); gc()
          ###Resample Data####
          decimalplaces <- function(x) {
            if ((x %% 1) != 0) {
              nchar(strsplit(sub('0+$', '', as.character(x)), ".", fixed=TRUE)[[1]][[2]])
            } else {
              return(0)
            }
          }
          
          dectest <- sample(data.frame(dat)[,1], 1000, replace=T)
          ndec <- max(sapply(dectest, decimalplaces))
          
          testdiv <- vlist$samprate / vlist$resampfz
          testdivint <- testdiv%%1==0
          dat1 <- if(testdiv >= 2 & testdivint==T){
            rsampdat <- function(x){
              x[seq(1, length(x), testdiv)]
            }
            data.frame(apply(dat, 2, rsampdat))
          } else if(testdiv == 1){
            dat
          } else{
            rsampdat1 <- function(x){
              round(gsignal::resample(x, vlist$resampfz, vlist$samprate), ndec)
            }
            data.frame(apply(dat, 2, rsampdat1))
          } ; gc()
          
          ###Match ADC Resolution####
          dat1 <- if(vlist$matchadc=="False"){
            dat1
          } else if(vlist$matchadc=="True" & testdiv >= 2 & testdivint==T){
            dat1
          } else {
            acl <- round(seq((dynrange*-1), dynrange, ((2*dynrange)/(2^bitval))), 4)
            nearest.vec <- function(x, acl){
              smallCandidate <- findInterval(x, acl, all.inside=TRUE)
              largeCandidate <- smallCandidate + 1
              #nudge is TRUE if large candidate is nearer, FALSE otherwise
              nudge <- 2 * x > acl[smallCandidate] + acl[largeCandidate]
              return(acl[smallCandidate + nudge])
            }
            data.frame(apply(dat1, 2, nearest.vec, acl))
          } ; gc()
          
          ####Recompute Indices####
          chnkfullre <- chnkfull*(vlist$resampfz/vlist$samprate)
          chnkfullrebot <- chnkbot*(vlist$resampfz/vlist$samprate)
          chnkfullretop <- chnktop*(vlist$resampfz/vlist$samprate)
          
          ####Work on Timestamp####
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
            as.POSIXct(tdat, format=tformfin, tz="UTC", origin = "1970-01-01")
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
            as.POSIXct(stival, format=stistruct, tz="UTC", origin = "1970-01-01")
          } else if(vlist$tstamp=="Yes3"){
            ###Starting Date/Time input by User####
            sdate <- vlist$sdate
            stime <- vlist$stime
            sdtime <- paste(sdate,stime)
            as.POSIXct(sdtime, format="%Y-%m-%d %H:%M:%S", tz="UTC", origin = "1970-01-01")
          }else{
            NULL
          }
          
          #####Create the Actual Timestamp#####
          dtimestamp <- if(is.null(tstampst)==F & is.null(as.POSIXct(as.character(tstampst),format="%Y-%m-%d %H:%M:%S", origin = "1970-01-01"))==F){
            format(seq(tstampst, (tstampst+(nrow(dat1))*(1/vlist$resampfz)), (1/vlist$resampfz)),"%Y-%m-%d %H:%M:%S")
          } else if(is.null(tstampst)){
            NULL
          } else{
            stop("Timestamp Error: Check Input Date/Time Parameters")
          }; gc()
          
          dtimestamp <- head(dtimestamp, nrow(dat1)); gc()
          
          #####Final Data#####
          if(is.null(dtimestamp)){
            findat <- dat1
          } else {
            findat <- data.frame(Timestamp = dtimestamp,dat1)
          }; gc()
          
          ####Subset Correct Indices#####
            if(iterval == 1 & iterlength == 1){
            findat
          }
            else if(iterval == 1 & iterlength > 1){
            findat <- head(findat, -(vlist$resampfz*120))
          } else if (iterval < itermax){
            findat <- head(tail(findat, -(vlist$resampfz*120)), -(vlist$resampfz*120))
          } else {
            findat <- tail(findat, -(vlist$resampfz*120))
          }
          
          ####Write the Data to File####
          fname <- if(substr(vlist$outdir, nchar(vlist$outdir), nchar(vlist$outdir)) == "/"){
            paste0(vlist$outdir,substr(basename(files),1,nchar(basename(files))-4),vlist$resampfz,"Hz")
          } else{
            paste0(vlist$outdir,"/",substr(basename(files),1,nchar(basename(files))-4),vlist$resampfz,"Hz")
          }
          
          for(i in 1:length(vlist$outform)){
            outformat <- vlist$outform[i]
            sepval2 <- ifelse(outformat==".csv", ",",
                              ifelse(outformat==".tab", "\t", " "))
            
            if(vlist$rethead=="False" & iterval == 1){
              data.table::fwrite(findat, paste0(fname,outformat), sep = sepval2, showProgress=F,verbose=F)
            } else if(vlist$rethead=="False" & iterval > 1){
              data.table::fwrite(findat, paste0(fname,outformat), sep = sepval2, showProgress=F,verbose=F,append=T, col.names=F)
            } else if(vlist$rethead == "True" & iterval == 1){
              hdlist <- lapply(1:(vlist$startrow - 1), function(x){
                skipval <- x-1
                hddat <- read.table(files, sep=sepval, header=F, nrows = 1, skip = skipval)
                hddat
              })
              write.table(hdlist[[1]], paste0(fname,outformat), sep = sepval2, quote=F, append=F, col.names=F, row.names=F, na = "")
              hdlist2 <- tail(hdlist, -1)
              lapply(hdlist2, function(x){
                write.table(x, paste0(fname,outformat), sep = sepval2, quote=F, append=T, col.names=F, row.names=F, na = "")
              })
              data.table::fwrite(findat[,-1], paste0(fname,outformat), sep = sepval2, showProgress=F,verbose=F,append=T, col.names=F)
            } else{
              data.table::fwrite(findat[,-1], paste0(fname,outformat), sep=sepval2, showProgress=F, verbose=F, append=T, col.names=F)
            }
          }
        }
        invisible(lapply(nchunks, mprocfunc))
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

###Run the Function###
procresampdata()