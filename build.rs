
use cpp_build;

fn main() {

    
    //let out_dir = PathBuf::from(env::var("OUT_DIR")
        //.expect("OUT_DIR env var is not defined"));
    let include_path = "/usr/home/basilisk/tapedeck/bsq/src";
    let include_path2 = "/usr/home/basilisk/tapedeck/bsq/src/bsqcustom";
    let lib_path = "/usr/local/lib/";
    let flag = "-std=c++17";
    //let lflag = "-lc++"; 
    cpp_build::Config::new().flag(flag).include(include_path).include(include_path2).build("/usr/home/basilisk/tapedeck/bsq/src/lib.rs");
    println!("cargo:rustc-link-search={}", lib_path);
    //println!("cargo:rustc-link-lib=myexternallib");
}