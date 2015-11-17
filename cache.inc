<?php
namespace cache;

abstract class Cache {
	private $disabled = false;
	private $hitcount = 0;
	private $misscount = 0;
	protected $hit = false;
	abstract public function setValue($key,$value);
	abstract public function getValue($key);
	abstract public function haveValue($key);
	
	public function get($key,callable $function) {
		if ($this->disabled == true ) {
			return call_user_func($function);
		}
		if ($this->haveValue($key)) {
			$this->hit = true;
			$this->hitcount++;
			return $this->getValue($key);
		}
		$this->misscount++;
		$this->hit = false;
		$value = call_user_func($function);
		$this->setValue($key,$value);
		return $value;
	}
	
	public function wasHit() {
		return $this->hit;
	}
	
	public function stats() {
		return array("hit"=>$this->hitcount,"miss"=>$this->misscount);
	}
	
	public function setDisabled($value) {
		$this->disabled = ($value==true?true:false);
	}
}