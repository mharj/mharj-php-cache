<?php
namespace cache;

abstract class Cache {
	private $disabled = false;
	private $hitcount = 0;
	private $misscount = 0;
	protected $hit = false;
	
	/**
	 * Set cache value
	 * @param string $key
	 * @param mixed $value
	 */
	abstract protected function setValue($key,$value);
	
	/**
	 * Get cache value
	 * @param string $key
	 * @return mixed
	 */
	abstract protected function getValue($key);
	
	/**
	 * Cache have value
	 * @param string $key
	 * @return boolean
	 */
	abstract protected function haveValue($key);
	
	/**
	 * Delete cache key/value
	 * @param string $key
	 * @return boolean
	 */	
	abstract public function delete($key);
	
	/**
	 * Get data from cache else use callback function to get data
	 * @param string $key
	 * @param callable $function
	 * @return mixed
	 */
	public function get($key,callable $function) {
		if ($this->disabled == true ) {
			$this->misscount++;
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
	protected function setHit() {
		$this->hitcount++;
	}
	protected function setMiss() {
		$this->misscount++;
	}
	/**
	 * if last get was from cache
	 * @return boolean
	 */
	public function wasHit() {
		return $this->hit;
	}
	
	/**
	 * get cache statistics
	 * @return array
	 */
	public function stats() {
		return array("hit"=>$this->hitcount,"miss"=>$this->misscount);
	}
	
	/**
	 * enable/disable cache
	 * @param boolean $value
	 */
	public function setDisabled($value) {
		$this->disabled = ($value==true?true:false);
	}
}