## ----setup, include=FALSE-----------------------------------------------------
knitr::opts_chunk$set(echo = TRUE, eval = FALSE)

## -----------------------------------------------------------------------------
#  install.packages("shinytest2")

## ---- code = readLines('simple-app/app.R')------------------------------------
#  library(shiny)
#  ui <- fluidPage(
#    textInput("name", "What is your name?"),
#    actionButton("greet", "Greet"),
#    textOutput("greeting")
#  )
#  server <- function(input, output, session) {
#    output$greeting <- renderText({
#      req(input$greet)
#      paste0("Hello ", isolate(input$name), "!")
#    })
#  }
#  shinyApp(ui, server)

## -----------------------------------------------------------------------------
#  library(shinytest2)
#  record_test("simple-app/")

## ----echo=FALSE, eval=TRUE, out.width='100%', fig.align='center'--------------
knitr::include_graphics("images/record-simple-app.png")

## ----echo=FALSE, eval=TRUE, out.width='100%', fig.align='center'--------------
knitr::include_graphics("images/record-simple-app-2.png")

## -----------------------------------------------------------------------------
#  # File: tests/testthat/test-shinytest2.R
#  library(shinytest2)
#  
#  test_that("{shinytest2} recording: simple-app", {
#    app <- AppDriver$new(name = "simple-app", height = 407, width = 348)
#    app$set_inputs(name = "Barret")
#    app$click("greet")
#    app$expect_values()
#  })

## -----------------------------------------------------------------------------
#  test_app("simple-app", filter = "shinytest2")

## ----echo=FALSE, eval=TRUE, out.width='100%', fig.align='center'--------------
knitr::include_graphics("images/diffviewer-1.png")

## ----echo=FALSE, eval=TRUE, out.width='100%', fig.align='center'--------------
knitr::include_graphics("images/record-name.png")

## -----------------------------------------------------------------------------
#  rmarkdown::shiny_prerendered_clean("../doc.Rmd")

