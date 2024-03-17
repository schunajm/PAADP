## ----setup, include=FALSE-----------------------------------------------------
library(shiny)
knitr::opts_chunk$set(echo = TRUE, eval = FALSE)

## -----------------------------------------------------------------------------
#  # File: tests/testthat/test-inst-apps.R
#  library(shinytest2)
#  
#  test_that("sample_app works", {
#    # Don't run these tests on the CRAN build servers
#    skip_on_cran()
#  
#    appdir <- system.file(package = "exPackage", "sample_app")
#    test_app(appdir)
#  })

## -----------------------------------------------------------------------------
#  # File: R/hello-world.R
#  
#  hello_world_app <- function() {
#    utils::data(cars)
#    shinyApp(
#      ui = fluidPage(
#        sliderInput("n", "n", 1, nrow(cars), 10),
#        plotOutput("plot")
#      ),
#      server = function(input, output) {
#        output$plot <- renderPlot({
#          plot(head(cars, input$n), xlim = range(cars[[1]]), ylim = range(cars[[2]]))
#        })
#      }
#    )
#  }

## -----------------------------------------------------------------------------
#  # File: tests/testthat/test-app-function.R
#  
#  test_that("hello-world app initial values are consistent", {
#    # Don't run these tests on the CRAN build servers
#    skip_on_cran()
#  
#    shiny_app <- hello_world_app()
#    app <- AppDriver$new(shiny_app, name = "hello")
#  
#    app$expect_values()
#  })

