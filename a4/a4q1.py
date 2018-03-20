






// monotone calculates
// total weight upto 'v'
// where w is the maximum local weight it can use
function monotone(v, w) {
  if (v == s) {
    return 0;
  }

  if (v < s) {
    return 'no'
  }

  ret = Number.POSITIVE_INFINITY;

  for (let edge in v.edges) {
    if (w(edge) < w) {
      let sub_ret = monotone(v.parent, w(edge)) + w(edge);
      if (sub_ret < ret) {
        ret = sub_ret;
      }
    }
  }

  return ret;

}

monotone(t, Number.POSITIVE_INFINITY);
