################################################################################
# Measure in N points (sizes) with K algorithms (search algorithms)
# with M runs (number of tests performed)
# N=13
# K=3
# M=20
################################################################################
require(stats)
rm(list=ls())

compare_times = function(results, algos, sizes)
{
   for(i in 1:length(algos))
   {
      a=algos[[i]][[1]]
      for(j in 1:length(sizes))
      {
         d=a[a$DATA == sizes[[j]], ]
         results[i, j]=mean(d$TIME)
      }
   }

   pdf("times.pdf")
   min_time = function(results, m){ for(i in 1:nrow(results)) {l = min(results[i, ]); if(l < m) m=l; }; m; }
   max_time = function(results, m){ for(i in 1:nrow(results)) {l = max(results[i, ]); if(l > m) m=l; }; m; }

   colors = c("blue", "red", "orange", "green", "brown")
   pchs = c(0,8,2,5,3)
   xlab = sizes[seq(1, length(sizes), 2)]
   leg_colors = c(1:nrow(results))
   leg_pchs = c(1:nrow(results))

   # plot
   plot(results[1,],
      ylim=c(min_time(results, 999999999999), max_time(results, -1)),
      pch=pchs[1], xaxt = "n", type="b", log="x",
      xlab="Size (# nodes)", ylab="Time (ms)", col=colors[1])

   # rename axis
   axis(1, at=seq(0,length(sizes),2), labels=xlab)

   # set values for legend
   leg_colors[1] = colors[1]
   leg_pchs[1] = pchs[1]

   for(i in 2:nrow(results))
   {
      # add lines
      lines(results[i,], col=colors[i])
      # add points
      points(results[i,], col=colors[i], pch=pchs[i])
      # set values for legend
      leg_colors[i] = colors[i]
      leg_pchs[i] = pchs[i]
   }

    # add a title
    title("Path finder - Elapsed time")
    # add a legend
    legend('topleft', legend=c("Uniform-Cost", "Greedy", "A*"), col=leg_colors, pch=leg_pchs, lty=1:2, cex=0.8, title="Algorithms")
    dev.off()
}

compare_costs = function(results, algos, sizes)
{
   for(i in 1:length(algos))
   {
      a=algos[[i]][[1]]
      for(j in 1:length(sizes))
      {
         d=a[a$DATA ==  sizes[[j]], ]
         results[i, j]=mean(d$COST)
      }
   }

   pdf("costs.pdf")
   min_cost = function(results, m){ for(i in 1:nrow(results)) {l = min(results[i, ]); if(l < m) m=l; }; m; }
   max_cost = function(results, m){ for(i in 1:nrow(results)) {l = max(results[i, ]); if(l > m) m=l; }; m; }

   # set up the plot
   colors= c("blue", "red", "orange", "green", "brown")
   xlab = sizes[seq(1, length(sizes), 1)]

   # plot
   barplot(results,
      xlab="Size (# nodes)", ylab="Path cost", names.arg = xlab, col=colors[seq(1,nrow(results),1)],
       beside=TRUE)

   # add a title
   title("Path finder - Path costs")
   # add a legend
   legend('topleft', legend=c("Uniform-Cost", "Greedy", "A*"), col=colors[seq(1,nrow(results),1)], lty=1, lwd=5, title="Algorithms")
   dev.off()
}

main = function()
{
   # set variables
   prefix = Sys.getenv("PATH_FINDER_ROOT")
   path = "/times/results/"
   file_path = gsub(" ", "", paste(prefix,path), fixed = TRUE)
   # change working dir
   setwd(file_path)

   # read files into data
   files = list.files(file_path)
   data = ""
   first = TRUE
   for(file in files)
   {
      to_append = read.csv(file, header = TRUE, sep = ",")
      if(first)
      {
         data = to_append
         first = FALSE
      }
      else
      {
         data = rbind(data, to_append)
      }
   }

   prefix = Sys.getenv("PATH_FINDER_ROOT")
   path = "/times/stats/"
   file_path = gsub(" ", "", paste(prefix,path), fixed = TRUE)
   # change working dir
   setwd(file_path)
   # set-up data
   data$DATA = as.numeric(data$DATA)
   data$TIME = as.numeric(data$TIME)
   data$COST = as.numeric(data$COST)
   data$ALGORITHM = as.numeric(data$ALGORITHM)
   data = data[order(data$DATA),]
   # group by algorithms
   algos= list()
   # O : Uniform
   # 1 : Greedy
   # 2 : Astar
   for(i in 0:length(unique(data$ALGORITHM)))
   {
      algos[[length(algos)+1]] = list(data[data$ALGORITHM == i, ])
   }
   # remove last zeros element from the set
   algos[[length(algos)]] = NULL

   sizes=unique(data$DATA)
   results=matrix(0,
         nrow=length(unique(data$ALGORITHM)),
         ncol=length(unique(data$DATA)))

   compare_costs(results, algos, sizes)
   compare_times(results, algos, sizes)
}

main()