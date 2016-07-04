# gembed

>*Disclaimer:* I am not a researcher and are not aware of the *state of the art* results for this kind of algorithms. I wrote the example as a minimalistic test but did not perform any benchmark with larger graph in higher dimension. The "API" is very crude and you should use it for experiment and fun only. ;) 

## What is this ?

*Gembed* is a force-directed (metric) graph embedding heuristic. Given a graph equiped with a metric (a map from its edges to the positive reals), it tries to find a mapping from the vertices to points in the k-dimesional euclidean space such that the distance in the graph approach square distance between the points of the space.

## What can I use this for ?

I wrote this code mainly for the fun of trying to design my own [word embedding](https://en.wikipedia.org/wiki/Word_embedding) algorithm but the few test I performed shows it could be used for graph drawing too.

##Hyperparameters and complexity


## Show me some code !

- ####TODOs

  - use and benchmark for word embedding
  - find a better stopping criterion than "preform N steps"
  - use other potential than ```std::log``` ?
